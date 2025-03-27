#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ifxAvian/Avian.h"
#include "ifxAlgo/FFT.h"
#include "ifxFmcw/DeviceFmcw.h"
#include "ifxFmcw/MetricsFmcw.h"
#include "ifxFmcw/DeviceFmcwTypes.h"
#include "ifxBase/Error.h"
#include "ifxBase/Version.h"
#include <unistd.h>
#include "ifxBase/Complex.h"
#include "pthread.h"

#define NUM_RX_ANTENNAS 1
#define FRAME_RATE 20.0
#define NUMBER_OF_CHIRPS 1
#define SAMPLES_PER_CHIRP 64
#define FFT_SIZE_RANGE_PROFILE (SAMPLES_PER_CHIRP * 2)
#define QUEUE_SIZE 50

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
    //ifx_Mda_R_t** slice;

    while(1){
        ifx_fmcw_get_next_frame(holder->device, frame);
        if (frame == NULL) {
            fprintf(stderr, "Failed to acquire frame: %s\n", ifx_error_to_string(ifx_error_get()));
            break; 
        }

        //slice = (ifx_Mda_R_t**)calloc(frame->num_cubes, sizeof(ifx_Mda_R_t*));
        
        for(uint32_t i = 0; i < frame->num_cubes; i++){
            //slice[i] = frame->cubes[i];
            //enqueue(&queue, slice[i]);
            enqueue(&queue, frame->cubes[i]);
        }
    }
    //free(slice);
    ifx_fmcw_destroy_frame(frame);
    return NULL;
}

// Function to simulate processing radar data
void* process_data_thread(void* arg) {
    while(1){
        if(!is_empty(&queue)){

            ifx_Mda_R_t* temp = dequeue(&queue);
            printf("Here is a frame: %f\n", temp->data[1]);
        }
    }
    return NULL;
}





int main(){
    init_queue(&queue);
    pthread_t data_thread, process_thread;
    ifx_Device_Fmcw_t* device = ifx_fmcw_create();
    
    if ((device = NULL) != IFX_OK){
        fprintf(stderr, "Failed to open device: %s\n", ifx_error_to_string(ifx_error_get()));
        return -1;
    }

    printf("Radar SDK Version: %s\n", ifx_sdk_get_version_string_full());
    printf("UUID of board: %s\n", ifx_avian_get_board_uuid(device));
    printf("Sensor: %u\n", ifx_avian_get_sensor_type(device));

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
    double max_range = range_res * single_chirp.chirp.num_samples / 2;
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
