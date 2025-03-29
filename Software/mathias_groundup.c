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
#define SAMPLES_PER_CHIRP 64
#define FFT_SIZE_RANGE_PROFILE (SAMPLES_PER_CHIRP * 2)
#define QUEUE_SIZE 50
#define OBJECT_DIST_START 0.5
#define OBJECT_DIST_END 0.6
#define BUFFER_SIZE 2000

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

/*size_t compute_offset(const ifx_Mda_R_t* array, const uint32_t* indices)
{
    size_t offset = 0;
    for (uint32_t i = 0; i < array->dimensions; ++i) {
        offset += indices[i] * array->stride[i];  // Compute offset using stride
    }
    return offset;
}

// Function to multiply frame by window coefficients
void apply_window_to_frame(ifx_Mda_R_t* frame, ifx_Mda_R_t* window)
{
    // Check that the dimensions and shape match
    if (frame->dimensions != window->dimensions) {
        printf("Error with Windowing");
        return;
    }

    for (uint32_t i = 0; i < frame->dimensions; ++i) {
        if (frame->shape[i] != window->shape[i]) {
            printf("Error with Windowing");
            return;
        }
    }

    // Number of elements in the frame (assuming multi-dimensional arrays)
    uint32_t num_elements = 1;
    for (uint32_t i = 0; i < frame->dimensions; ++i) {
        num_elements *= frame->shape[i];
    }

    // Temporary array to hold the indices for accessing frame and window elements
    uint32_t* indices = (uint32_t*)malloc(frame->dimensions * sizeof(uint32_t));

    // Multiply the data element by element, using stride-based indexing
    for (uint32_t i = 0; i < num_elements; ++i) {
        // Compute multi-dimensional indices for the current element
        uint32_t temp_i = i;
        for (uint32_t d = 0; d < frame->dimensions; ++d) {
            indices[d] = temp_i % frame->shape[d];  // Get index for dimension d
            temp_i /= frame->shape[d];  // Move to the next "layer"
        }

        // Compute the offset for frame and window data
        size_t frame_offset = compute_offset(frame, indices);
        size_t window_offset = compute_offset(window, indices);

        // Multiply the frame's data by the corresponding window coefficient
        frame->data[frame_offset] *= window->data[window_offset];
    }

    // Clean up
    free(indices);
}*/

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

void vital_signs_fft(float* input, float* output, int length, int scalar){
    ifx_Vector_R_t* in_sig = ifx_vec_create_r((uint32_t)length);
    ifx_Vector_C_t* out_fft = ifx_vec_create_c((uint32_t)length);
    ifx_Vector_R_t* out_abs = ifx_vec_create_r((uint32_t)length);
    ifx_Vector_R_t* out_sig = ifx_vec_create_r((uint32_t)length);

    ifx_vec_rawview_r(in_sig, input, length, 1);

    ifx_Window_Config_t wnd;
    wnd.type = IFX_WINDOW_BLACKMANHARRIS;
    wnd.size = length;
    wnd.scale = 1;
	 
    ifx_PPFFT_Config_t fft_config;
    fft_config.fft_size = scalar;
    fft_config.fft_type = IFX_FFT_TYPE_R2C;
    fft_config.is_normalized_window = false;
    fft_config.mean_removal_enabled = false;
    fft_config.window_config = wnd;

    ifx_PPFFT_t* fft_tool = ifx_ppfft_create(&fft_config);

    ifx_ppfft_run_rc(fft_tool, in_sig, out_fft);

    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed to compute fft: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(fft_tool);
            return;
        }     
        
    ifx_vec_abs_c(out_fft, out_abs);

    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed to compute fft: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(fft_tool);
            return;
        }     
        
    ifx_vec_scale_r(out_abs, 1/scalar, out_sig);

    if (ifx_error_get() != IFX_OK) {
            fprintf(stderr, "Failed to compute fft: %s\n", ifx_error_to_string(ifx_error_get()));
            ifx_ppfft_destroy(fft_tool);
            return;
        }     

    for(int i = 0; i < length; i++){
        output[i] = out_sig->data[i];
    }

    ifx_vec_destroy_r(in_sig);
    ifx_vec_destroy_r(out_abs);
    ifx_vec_destroy_r(out_fft);
    ifx_vec_destroy_c(out_sig);
    ifx_ppfft_destroy(fft_tool);
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
        
        
        
        //ifx_window_init(&wnd, &coeff);
        //apply_window_to_frame(frame, &coeff);
       
        ifx_mat_destroy_r(temp_m);
        ifx_vec_destroy_r(temp_v);
    }
    ifx_ppfft_destroy(fft_tool);
}

// Function to simulate processing radar data
void* process_data_thread(void* arg) {

    ifx_Vector_C_t* range_fft = ifx_vec_create_c(SAMPLES_PER_CHIRP);
    ifx_Vector_R_t* range_fft_abs = ifx_vec_create_r(SAMPLES_PER_CHIRP);
    ifx_Complex_t slow_time_buffer[BUFFER_SIZE] = {0};

    int start_index = (int)(OBJECT_DIST_START/max_range * SAMPLES_PER_CHIRP);
    int end_index = (int)(OBJECT_DIST_END/max_range * SAMPLES_PER_CHIRP);
    int peak_indeces[2*(int)FRAME_RATE] = {0};
    int peak_index_avg = 0;
    float max_val;
    int sum;
    int counter = 0;
    float wrapped_phase_plot[BUFFER_SIZE] = {0};
    float unwrapped_phase_plot[BUFFER_SIZE] = {0};
    float filtered_breathing_plot[BUFFER_SIZE] = {0};
    float filtered_heart_plot[BUFFER_SIZE] = {0};

    while(1){
        if(!is_empty(&queue)){

            calc_range_fft(range_fft);
            //printf("Here is the fft data: %f\n", range_fft->data->data[0]);
            ifx_vec_abs_c(range_fft, range_fft_abs);

            for(int i = 0; i < (2*(int)FRAME_RATE) - 1; i++){
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
                    peak_indeces[(2*(int)FRAME_RATE)-1] = i;
                }
            }

            for(int i = 0; i < 2*(int)FRAME_RATE; i++){
                sum += peak_indeces[i];
            }

            peak_index_avg = (int)(sum/(2*(int)FRAME_RATE));

            slow_time_buffer[BUFFER_SIZE-1] = range_fft->data[peak_index_avg];

            if(counter < BUFFER_SIZE-1){
                counter++;
            }
            //printf("peak: %f\n", max_val);
            //printf("avg: %u\n", peak_index_avg);

            float wrapped_phase[counter];
            float unwrapped_phase[counter];

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
				
				float filtered_breathing[counter];
    			float filtered_heart[counter];				
				
            fir_filter(unwrapped_phase, filtered_breathing, breathing_b, counter, (int)FRAME_RATE + 1);
            fir_filter(unwrapped_phase, filtered_heart, heart_b, counter, (int)FRAME_RATE + 1); //skipped a part in python

            j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                unwrapped_phase_plot[i] = unwrapped_phase[j];
                j++;
            }

            j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                filtered_breathing_plot[i] = filtered_breathing[j];
                j++;
            }

            j = 0;
            for(int i = BUFFER_SIZE - counter; i < BUFFER_SIZE; i++){
                filtered_heart_plot[i] = filtered_heart[j];
                j++;
            }
            //printf("peak: %f\n", filtered_breathing_plot[BUFFER_SIZE-1]);
            //printf("peak: %f\n", filtered_heart_plot[BUFFER_SIZE-1]);

            float breathing_fft[counter];
            float heart_fft[counter];

            vital_signs_fft(filtered_breathing, breathing_fft, counter, BUFFER_SIZE);
            vital_signs_fft(filtered_heart, heart_fft, counter, BUFFER_SIZE);

            printf("peak: %f\n", breathing_fft[0]);
            printf("peak: %f\n", heart_fft[0]);
        }
    }
    ifx_vec_destroy_r(range_fft_abs);
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
    single_chirp.chirp.sample_rate_Hz = 1e6;
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
    /*ifx_Fmcw_Frame_t* frame = ifx_fmcw_allocate_frame(device);

    while(1){

        ifx_fmcw_get_next_frame(device, frame);
        if (frame == NULL) {
            fprintf(stderr, "Failed to acquire frame: %s\n", ifx_error_to_string(ifx_error_get()));
            break; 
        }

        usleep(1000);
    }
*/  pthread_join(data_thread, NULL);
    pthread_join(process_thread, NULL);

    pthread_mutex_destroy(&queue.mutex);  // Destroy the mutex
    ifx_fmcw_destroy_sequence(sequence);
  //  ifx_fmcw_destroy_frame(frame);
    ifx_fmcw_destroy(device);
}
