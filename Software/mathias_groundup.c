#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ifxAvian/Avian.h"
#include "ifxAlgo/FFT.h"
#include "ifxAlgo/Window.h"
#include "ifxFmcw/DeviceFmcw.h"
#include "ifxFmcw/MetricsFmcw.h"
#include "ifxFmcw/DeviceFmcwTypes.h"
#include "ifxBase/Error.h"
#include "ifxBase/Version.h"
#include <unistd.h>
#include "ifxBase/Complex.h"
#include "pthread.h"
#include "ifxAlgo/PreprocessedFFT.h"

// Define M_PI manually if it is still not recognized
#define M_PI 3.14159265358979323846

#define NUM_RX_ANTENNAS 1
#define FRAME_RATE 20.0
#define NUMBER_OF_CHIRPS 1
#define SAMPLES_PER_CHIRP 128
#define FFT_SIZE_RANGE_PROFILE (SAMPLES_PER_CHIRP * 2)
#define QUEUE_SIZE 50
#define OBJECT_DIST_START 0.5
#define OBJECT_DIST_END 1.5
#define BUFFER_SIZE 256 //must be a power of 2
#define FFT_SIZE_2 (BUFFER_SIZE * 2);

//The following were used in
//a python script to create the filter coefficients
#define LOW_BREATHING 0.15
#define HIGH_BREATHING 0.6
#define LOW_HEART 0.85
#define HIGH_HEART 2.4

// Define the queue structure
typedef struct {
    ifx_Mda_R_t *data[QUEUE_SIZE];   // Array to store queue elements
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    pthread_mutex_t mutex;  // Mutex for thread-safe access
} Queue;

// Global queue
Queue queue;
double max_range;

const float breathing_b[(int)FRAME_RATE+1] = {
    0.003224461484620409,
    0.0053625468955774,
    0.010716753679115535,
    0.020134452875849942,
    0.03364992753594613,
    0.05040530764097441,
    0.06875002737429206,
    0.08650406008875909,
    0.10133621147139964,
    0.11118431769162093,
    0.11463454748746789,
    0.11118431769162093,
    0.10133621147139964,
    0.08650406008875909,
    0.06875002737429206,
    0.05040530764097441,
    0.03364992753594613,
    0.020134452875849942,
    0.010716753679115535,
    0.0053625468955774,
    0.003224461484620409,
};

const float heart_b[(int)FRAME_RATE+1] = {
    0.0017645272119925645,
    -0.0009666883792551835,
    -0.010176268245414486,
    -0.03076649977892691,
    -0.058311372455515466,
    -0.07476801518027178,
    -0.05682865595727649,
    0.006279361489023919,
    0.09895901033453573,
    0.18246542149313824,
    0.21607567177986248,
    0.18246542149313824,
    0.09895901033453573,
    0.006279361489023919,
    -0.05682865595727649,
    -0.07476801518027178,
    -0.058311372455515466,
    -0.03076649977892691,
    -0.010176268245414486,
    -0.0009666883792551835,
    0.0017645272119925645,
};

void fir_filter(float* x, float* y, const float* b, int input_size, int filter_order) {
    // Loop through the input signal
    for (int n = 0; n < input_size; n++) {
        y[n] = 0;  // Initialize output

        // Apply the FIR filter
        for (int k = 0; k <= filter_order; k++) {
            if (n - k >= 0) {
                y[n] += b[k] * x[n - k];  // Convolution sum
            }
        }
    }
}

// Initialize the queue
void init_queue(Queue* q) {
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    pthread_mutex_init(&q->mutex, NULL);  // Initialize the mutex
}

// Check if the queue is empty
int is_empty(Queue* q) {
    return q->size == 0;
}

// Check if the queue is full
int is_full(Queue* q) {
    return q->size == QUEUE_SIZE;
}

// Enqueue operation to add an element to the queue
void enqueue(Queue* q, ifx_Mda_R_t* item) {
    pthread_mutex_lock(&q->mutex);  // Lock the mutex to ensure thread safety

    if (is_full(q)) {
        printf("Queue is full! Cannot enqueue");
    } else {
        q->data[q->head] = item;
        q->size++;
        q->head = (q->head + 1) % QUEUE_SIZE;
    }

    pthread_mutex_unlock(&q->mutex);  // Unlock the mutex
}

// Dequeue operation to remove an element from the queue
ifx_Mda_R_t* dequeue(Queue* q) {
    pthread_mutex_lock(&q->mutex);  // Lock the mutex to ensure thread safety

    ifx_Mda_R_t* item = NULL; // Default return value in case queue is empty
    if (is_empty(q)) {
        printf("Queue is empty! Cannot dequeue\n");
    } else {
        item = q->data[q->tail];
        q->tail = (q->tail + 1) % QUEUE_SIZE;
        q->size--;
    }

    pthread_mutex_unlock(&q->mutex);  // Unlock the mutex
    return item;
}




// Sample structure to pass data to the threads
typedef struct {
    ifx_Device_Fmcw_t* device;  // Device object
} ThreadArgs;

// Function to simulate reading data from the device
void* read_data_thread(void* arg) {
    ThreadArgs* holder = (ThreadArgs*) arg;
    ifx_Fmcw_Frame_t* frame = ifx_fmcw_allocate_frame(holder->device);

    while(1){
        ifx_fmcw_get_next_frame(holder->device, frame);
        if (frame == NULL) {
            fprintf(stderr, "Failed to acquire frame: %s\n", ifx_error_to_string(ifx_error_get()));
            break; 
        }

        
        for(uint32_t i = 0; i < frame->num_cubes; i++){
            enqueue(&queue, frame->cubes[i]);
        }
    }
    ifx_fmcw_destroy_frame(frame);
    return NULL;
}



void unwrap_phase(float* phase, int size) {
    // Iterate through the array of phase values
    for (int i = 1; i < size; i++) {
        // Compute the difference between the current phase and the previous one
        float delta = phase[i] - phase[i - 1];
        
        // If the difference exceeds pi, unwrap it by adding or subtracting 2*pi
        if (delta > M_PI) {
            phase[i] -= 2 * M_PI;  // Subtract 2*pi if the jump is greater than pi
        }
        else if (delta < -M_PI) {
            phase[i] += 2 * M_PI;  // Add 2*pi if the jump is less than -pi
        }
    }
}

int find_signal_peaks(float* fft_sig, int start_index, int end_index){
    float max_val = 0;
    int peak_index = 0;
    
    for (int i = start_index+1; i < end_index; i++) {
		  //printf("fft: %f\n", fft_sig[i]);    	
        if (fft_sig[i] > fft_sig[i - 1] && fft_sig[i] > fft_sig[i + 1]) {
            // This is a peak, so store the index
            if(max_val < fft_sig[i]){
                peak_index = i;
                max_val = fft_sig[i];
            }
        }
    }

    return peak_index;
}

void vital_signs_fft(float* input, float* output, int length){
    ifx_Vector_R_t* in_sig = ifx_vec_create_r((uint32_t)length);
    ifx_Vector_C_t* out_fft = ifx_vec_create_c((uint32_t)length);
    ifx_Vector_R_t* out_sig = ifx_vec_create_r((uint32_t)length);

    ifx_vec_rawview_r(in_sig, input, (uint32_t)length, 1);
    
    
    ifx_Window_Config_t sl_wnd;
    sl_wnd.type = IFX_WINDOW_BLACKMANHARRIS;
    sl_wnd.size = length;
    sl_wnd.scale = 1;
	 
    ifx_PPFFT_Config_t sl_fft_config;
    sl_fft_config.fft_size = FFT_SIZE_2;
    sl_fft_config.fft_type = IFX_FFT_TYPE_R2C;
    sl_fft_config.is_normalized_window = false;
    sl_fft_config.mean_removal_enabled = false;
    sl_fft_config.window_config = sl_wnd;

    ifx_PPFFT_t* sl_fft_tool = ifx_ppfft_create(&sl_fft_config);
    //ifx_FFT_t* tool_fft = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_2);
    
    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed create tool: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(sl_fft_tool);
            return;
        }

    
    if(sl_fft_tool == NULL){
    			printf("1\n");
    }
    if(in_sig == NULL){
    			printf("2");
    }
    if(out_fft == NULL){
    			printf("3");
    }
	 
	 //ifx_fft_run_rc(tool_fft, in_sig, out_fft);
    ifx_ppfft_run_rc(sl_fft_tool, in_sig, out_fft);

    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed vital_sign fft: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(sl_fft_tool);
            return;
        }     
        
    ifx_vec_abs_c(out_fft, out_sig);

    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed to compute abs: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(sl_fft_tool);
            return;
        }     

    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed to scale: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(sl_fft_tool);
            return;
        }     

    for(int i = 0; i < length; i++){
        output[i] = out_sig->data[i];
    }

    ifx_vec_destroy_r(in_sig);
    ifx_vec_destroy_c(out_fft);
    ifx_vec_destroy_r(out_sig);
    ifx_ppfft_destroy(sl_fft_tool);
}

void calc_range_fft(ifx_Vector_C_t* range_fft){

    ifx_Window_Config_t wnd;
    wnd.type = IFX_WINDOW_BLACKMANHARRIS;
    wnd.size = FFT_SIZE_RANGE_PROFILE/2;
    wnd.scale = 1;
	 
    ifx_PPFFT_Config_t fft_config;
    fft_config.fft_size = FFT_SIZE_RANGE_PROFILE;
    fft_config.fft_type = IFX_FFT_TYPE_R2C;
    fft_config.is_normalized_window = false;
    fft_config.mean_removal_enabled = false;
    fft_config.window_config = wnd;
    
    ifx_PPFFT_t* fft_tool = ifx_ppfft_create(&fft_config);

    if(!is_empty(&queue)){

        ifx_Mda_R_t *frame = dequeue(&queue);
        ifx_Matrix_R_t* temp_m = ifx_mat_create_r(frame->shape[0], frame->shape[2]);
        ifx_Vector_R_t* temp_v = ifx_vec_create_r(frame->shape[2]);
        
        ifx_cube_get_col_r(frame, 0, temp_m);
        ifx_mat_get_rowview_r(temp_m, 0, temp_v);
        
        ifx_ppfft_run_rc(fft_tool, temp_v, range_fft);
					
			
        if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed to compute fft: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(fft_tool);
            return;
        }     
        
       
        ifx_mat_destroy_r(temp_m);
        ifx_vec_destroy_r(temp_v);
    }
    ifx_ppfft_destroy(fft_tool);
}

// Function to simulate processing radar data
void* process_data_thread(void* arg) {

    ifx_Vector_C_t* range_fft = ifx_vec_create_c(SAMPLES_PER_CHIRP);
    ifx_Vector_R_t* range_fft_abs = ifx_vec_create_r(SAMPLES_PER_CHIRP);
    ifx_Vector_R_t* range_profile = ifx_vec_create_r(SAMPLES_PER_CHIRP);
    ifx_Vector_R_t* vitals_range_profile = ifx_vec_create_r(BUFFER_SIZE);
    ifx_Complex_t slow_time_buffer[BUFFER_SIZE] = {0};

    ifx_vec_linspace_r(0, max_range, range_profile);
    ifx_vec_linspace_r(0, FRAME_RATE/2, vitals_range_profile);

    int start_index = (int)(OBJECT_DIST_START/max_range * SAMPLES_PER_CHIRP);
    int end_index = (int)(OBJECT_DIST_END/max_range * SAMPLES_PER_CHIRP);
    
    int index_start_breathing = (int)(LOW_BREATHING/FRAME_RATE * 2 * BUFFER_SIZE); //in python, don't use BUFFER_SIZE,
    int index_end_brething = (int)(HIGH_BREATHING/FRAME_RATE * 2 * BUFFER_SIZE);    //double it.
    int index_start_heart = (int)(LOW_HEART/FRAME_RATE * 2 * BUFFER_SIZE);
    int index_end_heart = (int)(HIGH_HEART/FRAME_RATE * 2 * BUFFER_SIZE);

    int peak_indeces[BUFFER_SIZE] = {0};
    int peak_index_avg = 0;
    float max_val;
    int sum;
    int counter = 0;
    float wrapped_phase[BUFFER_SIZE] = {0};
    float unwrapped_phase[BUFFER_SIZE] = {0};
    float wrapped_phase_plot[BUFFER_SIZE] = {0};
    float unwrapped_phase_plot[BUFFER_SIZE] = {0};
    float filtered_breathing[BUFFER_SIZE] = {0};
    float filtered_heart[BUFFER_SIZE] = {0};	
    float filtered_breathing_plot[BUFFER_SIZE] = {0};
    float filtered_heart_plot[BUFFER_SIZE] = {0};
    float breathing_fft[BUFFER_SIZE] = {0};
    float heart_fft[BUFFER_SIZE] = {0};
    int breathing_rate_estimation_index[BUFFER_SIZE] = {0};
    int heart_rate_estimation_index[BUFFER_SIZE] = {0};
    int vital_sum = 0;
    int avg_breathing_index = 0;
    int avg_heart_index = 0;
    float breathing_fft_plot[BUFFER_SIZE] = {0};
    float heart_fft_plot[BUFFER_SIZE] = {0};
    float avg_b_fft = 0;
    float avg_h_fft = 0;
    float b_bpm = 0;
    float h_bpm = 0;
    float distance = 0;

    while(1){
        if(!is_empty(&queue)){

            calc_range_fft(range_fft);
            //printf("Here is the fft data: %f\n", range_fft->data->data[0]);
            ifx_vec_abs_c(range_fft, range_fft_abs);

            for(int i = 0; i < (BUFFER_SIZE) - 1; i++){
                peak_indeces[i] = peak_indeces[i+1];
            }
            for(int i = 0; i < (BUFFER_SIZE) - 1; i++){
                slow_time_buffer[i] = slow_time_buffer[i+1];
            }

            max_val = 0;
            sum = 0;

            for(int i = start_index; i <= end_index; i++){
                if(range_fft_abs->data[i] > max_val){
                    max_val = range_fft_abs->data[i];
                    peak_indeces[BUFFER_SIZE-1] = i;
                }
                //printf("\rrange: %f\n", range_fft_abs->data[i]);
                //printf("\rrange: %f\n", range_fft_abs->data[i]);
            }

            for(int i = 0; i < BUFFER_SIZE; i++){
                sum += peak_indeces[i];
            }

            peak_index_avg = (int)(sum/(BUFFER_SIZE));
				
				distance = range_profile->data[peak_index_avg];
				
            slow_time_buffer[BUFFER_SIZE-1] = range_fft->data[peak_index_avg];
            
            heart_fft_plot[BUFFER_SIZE-1] = range_fft_abs->data[peak_index_avg];
            
			        /*    max_val = 0;
			            for(int i = BUFFER_SIZE-counter; i < BUFFER_SIZE; i++){
								max_val += heart_fft_plot[i];				          
			            }
			            
			            avg_h_fft = max_val/counter;*/

            if(counter < BUFFER_SIZE){
                counter++;
            }
            //printf("peak: %f\n", max_val);
            
				//printf("stb: %f\n", slow_time_buffer[((BUFFER_SIZE-1)-counter)+i].data[1]);
				
            for(int i = 0; i < counter; i++){
                wrapped_phase[i] = (float)atan2(slow_time_buffer[((BUFFER_SIZE-1)-counter)+i].data[1],
                                                slow_time_buffer[((BUFFER_SIZE-1)-counter)+i].data[0]);
            }

            for(int i = 0; i < BUFFER_SIZE - counter; i++){
                wrapped_phase_plot[i] = wrapped_phase_plot[i+counter];
            }

            int j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                wrapped_phase_plot[i] = wrapped_phase[j];
            	 //printf("peak: %f\n", wrapped_phase[j]);
                j++;
            }
            //printf("peak: %f\n", wrapped_phase_plot[BUFFER_SIZE-1]);
            //printf("avg: %u\n", counter);
				
            for(int i = 0; i < counter; i++){
                unwrapped_phase[i] = wrapped_phase[i];
            }
            
            unwrap_phase(unwrapped_phase, counter);
            
            for(int i = 0; i < BUFFER_SIZE - (int)counter; i++){
                unwrapped_phase_plot[i] = unwrapped_phase_plot[i+counter];
            }
			
            j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                unwrapped_phase_plot[i] = unwrapped_phase[j];
            	 //printf("peak: %f\n", unwrapped_phase[j]);
                j++;
            }
				
            fir_filter(unwrapped_phase, filtered_breathing, breathing_b, counter, (int)FRAME_RATE + 1);
            fir_filter(unwrapped_phase, filtered_heart, heart_b, counter, (int)FRAME_RATE + 1); //skipped a part in python

            
            for(int i = 0; i < BUFFER_SIZE - (int)counter; i++){
                filtered_breathing_plot[i] = filtered_breathing_plot[i+counter];
            }

            for(int i = 0; i < BUFFER_SIZE - (int)counter; i++){
                filtered_heart_plot[i] = filtered_heart_plot[i+counter];
            }

            j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                filtered_breathing_plot[i] = filtered_breathing[j];
            	 //printf("peak: %f\n", filtered_breathing[j]);
                j++;
            }

            j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                filtered_heart_plot[i] = filtered_heart[j];
            	 //printf("peak: %f\n", filtered_heart[j]);                
                j++;
            }
            //printf("peak: %f\n", filtered_breathing_plot[BUFFER_SIZE-1]);
            //printf("peak: %f\n", filtered_heart_plot[BUFFER_SIZE-1]);

            
			if(counter > 10){
                vital_signs_fft(filtered_breathing_plot, breathing_fft, BUFFER_SIZE);
                vital_signs_fft(filtered_heart_plot, heart_fft, BUFFER_SIZE);
            }

            //printf("b: %f\n", breathing_fft[0]);
            //printf("h: %f\n", heart_fft[0]);

            for(int i = 0; i < BUFFER_SIZE - 1; i++){
                breathing_rate_estimation_index[i] = breathing_rate_estimation_index[i+1];
            }

            for(int i = 0; i < BUFFER_SIZE - 1; i++){
                heart_rate_estimation_index[i] = heart_rate_estimation_index[i+1];
            }

            breathing_rate_estimation_index[BUFFER_SIZE-1] = find_signal_peaks(breathing_fft, index_start_breathing, index_end_brething);//may not work
            heart_rate_estimation_index[BUFFER_SIZE-1] = find_signal_peaks(heart_fft, index_start_heart, index_end_heart);//as max value and not peak will
                                                                                        //be returned
                                                                                        
            if(breathing_rate_estimation_index[BUFFER_SIZE-1] == 0){
					breathing_rate_estimation_index[BUFFER_SIZE-1] = breathing_rate_estimation_index[BUFFER_SIZE-2];            
            }
            
            if(heart_rate_estimation_index[BUFFER_SIZE-1] == 0){
					heart_rate_estimation_index[BUFFER_SIZE-1] = heart_rate_estimation_index[BUFFER_SIZE-2];            
            }max_val = 0;
            for(int i = BUFFER_SIZE-counter; i < BUFFER_SIZE; i++){
					max_val += heart_fft[i];				          
            }
            
            avg_h_fft = max_val/counter;
            
				vital_sum = 0;
				avg_breathing_index = 0;
				
            for(int i = BUFFER_SIZE-counter; i < BUFFER_SIZE; i++){
                vital_sum += breathing_rate_estimation_index[i];
            }

            avg_breathing_index = (int)(vital_sum/counter);
            
            vital_sum = 0;
				avg_heart_index = 0;

            for(int i = BUFFER_SIZE-counter; i < BUFFER_SIZE; i++){
                vital_sum += heart_rate_estimation_index[i];
            }

            avg_heart_index = (int)(vital_sum/counter);
				
				//printf("avg_h_index: %u\n", avg_heart_index);
				//printf("avg_b_index: %u\n", breathing_rate_estimation_index[BUFFER_SIZE-1]);
					
            b_bpm = vitals_range_profile->data[avg_breathing_index]*60;
            h_bpm = vitals_range_profile->data[avg_heart_index]*60;
            
            
            for(int i = 0; i < (BUFFER_SIZE) - 1; i++){
                breathing_fft_plot[i] = breathing_fft_plot[i+1];
                heart_fft_plot[i] = heart_fft_plot[i+1];
            }
            
            breathing_fft_plot[BUFFER_SIZE-1] = breathing_fft[breathing_rate_estimation_index[BUFFER_SIZE-1]];
            heart_fft_plot[BUFFER_SIZE-1] = heart_fft[heart_rate_estimation_index[BUFFER_SIZE-1]];
            
            max_val = 0;
            for(int i = BUFFER_SIZE-counter; i < BUFFER_SIZE; i++){
					max_val += breathing_fft[i];				          
            }
            
            avg_b_fft = max_val/counter;
            
            max_val = 0;
            for(int i = BUFFER_SIZE-counter; i < BUFFER_SIZE; i++){
					max_val += heart_fft[i];				          
            }
            
            avg_h_fft = max_val/counter;
            
            printf("mag b: %f\n", avg_b_fft);
            printf("mag h: %f\n", avg_h_fft);
            
            printf("distance: %f m\n", distance);
            printf("b_bpm: %f\n", b_bpm);
            printf("h_bpm: %f\n", h_bpm);
            //printf("counter: %u\n", counter);
        }
    }
    ifx_vec_destroy_r(range_fft_abs);
    ifx_vec_destroy_r(range_profile);
    ifx_vec_destroy_r(vitals_range_profile);
    ifx_vec_destroy_c(range_fft);
    
    return NULL;
}





int main(){
    init_queue(&queue);
    pthread_t data_thread, process_thread;
    ifx_Device_Fmcw_t* device = ifx_fmcw_create();
    
    if ((device == NULL) != IFX_OK){
        fprintf(stderr, "Failed to open device: %s\n", ifx_error_to_string(ifx_error_get()));
        return -1;
    }

    printf("Radar SDK Version: %s\n", ifx_sdk_get_version_string_full());
    printf("UUID of board: %s\n", ifx_fmcw_get_board_uuid(device));
    printf("Sensor: %u\n", ifx_fmcw_get_sensor_type(device));

    ifx_Fmcw_Simple_Sequence_Config_t single_chirp;
    single_chirp.num_chirps = NUMBER_OF_CHIRPS;
    single_chirp.chirp_repetition_time_s = 0.001;
    single_chirp.frame_repetition_time_s = 1 / FRAME_RATE;
    single_chirp.tdm_mimo = true;
    single_chirp.chirp.start_frequency_Hz = 57.4e9;
    single_chirp.chirp.end_frequency_Hz = 63.0e9;      //check these values on windows partition!!!!!
    single_chirp.chirp.sample_rate_Hz = 2e6;
    single_chirp.chirp.num_samples = SAMPLES_PER_CHIRP;
    single_chirp.chirp.rx_mask = 1;
    single_chirp.chirp.tx_mask = 1;
    single_chirp.chirp.tx_power_level = 31;
    single_chirp.chirp.lp_cutoff_Hz = 500000;
    single_chirp.chirp.hp_cutoff_Hz = 80000;
    single_chirp.chirp.if_gain_dB = 33;

    ifx_Fmcw_Sequence_Element_t* sequence = ifx_fmcw_create_simple_sequence(&single_chirp);
    ifx_fmcw_set_acquisition_sequence(device, sequence);

    // Check for errors after setting the configuration
    if (ifx_error_get() != IFX_OK) {
        fprintf(stderr, "Failed to configure radar device: %s\n", ifx_error_to_string(ifx_error_get()));
        ifx_avian_destroy(device);
        return -1;
    }

    double range_res = 3e8 / (2 * ifx_fmcw_get_chirp_sampling_bandwidth(device, &single_chirp.chirp));
    printf("Range resolution: %.3f m\n", range_res);
    max_range = range_res * single_chirp.chirp.num_samples / 2;
    printf("Maximum range: %.3f m\n", max_range);

    ThreadArgs variable;
    variable.device = device;

    // Create the thread for reading data from the device
    if (pthread_create(&data_thread, NULL, read_data_thread, (void*)&variable) != 0) {
        perror("Failed to create data thread");
        return 1;
    }

    // Create the thread for processing radar data
    if (pthread_create(&process_thread, NULL, process_data_thread, NULL) != 0) {
        perror("Failed to create process thread");
        return 1;
    }
    
  
    pthread_join(data_thread, NULL);
    pthread_join(process_thread, NULL);

    pthread_mutex_destroy(&queue.mutex);  // Destroy the mutex
    ifx_fmcw_destroy_sequence(sequence);
  //  ifx_fmcw_destroy_frame(frame);
    ifx_fmcw_destroy(device);
}
