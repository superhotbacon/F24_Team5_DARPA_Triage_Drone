#define _USE_MATH_DEFINES
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


// Define M_PI manually if it is still not recognized
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define NUM_RX_ANTENNAS 1
#define FRAME_RATE 20.0
#define NUMBER_OF_CHIRPS 8
#define SAMPLES_PER_CHIRP 64
#define FFT_SIZE_RANGE_PROFILE (SAMPLES_PER_CHIRP * 2)
#define PHASE_BUFFER_SIZE 400
#define FFT_SIZE_VITAL 2048 //Was originally 1600
#define LOW_BREATHING 0.15
#define HIGH_BREATHING 0.6
#define LOW_HEART 0.85
#define HIGH_HEART 2.4
#define FILTER_ORDER 21
#define OBJECT_DIST_START 0.5
#define OBJECT_DIST_STOP 0.6
#define VITAL_SIG_SAMPLE_RATE FRAME_RATE

static ifx_Float_t phase_buffer[PHASE_BUFFER_SIZE];
static int phase_index = 0;
int segFaultFinder = 0;
const ifx_Float_t breathing_b[FILTER_ORDER] = {
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476
};
const ifx_Float_t heart_b[FILTER_ORDER] = {
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476, 0.0476, 0.0476, 0.0476, 0.0476,
    0.0476
};

void fir_filter(const ifx_Float_t* b, int b_len, const ifx_Float_t* input, int input_len, ifx_Float_t* output) {
    for (int n = 0; n < input_len; n++) {
        ifx_Float_t acc = 0.0;
        for (int k = 0; k < b_len; k++) {
            if (n - k >= 0)
                acc += b[k] * input[n - k];
        }
        output[n] = acc;
    }
}

void unwrap_phase(ifx_Float_t* phase, int len) {
    for (int i = 1; i < len; i++) {
        ifx_Float_t dp = phase[i] - phase[i-1];
        if (dp > M_PI) {
            for (int j = i; j < len; j++) {
                phase[j] -= 2 * M_PI;
            }
        } else if (dp < -M_PI) {
            for (int j = i; j < len; j++) {
                phase[j] += 2 * M_PI;
            }
        }
    }
}

void process_vital_signs(const ifx_Float_t* phase_buf, int len) {
    int i;
    int processNum = 0;
    ifx_Float_t unwrapped_phase[PHASE_BUFFER_SIZE];
    for (i = 0; i < len; i++) {
        unwrapped_phase[i] = phase_buf[i];
    }
    unwrap_phase(unwrapped_phase, len);
    
    ifx_Float_t filtered_breathing[PHASE_BUFFER_SIZE] = {0};
    ifx_Float_t filtered_heart[PHASE_BUFFER_SIZE] = {0};
    fir_filter(breathing_b, FILTER_ORDER, unwrapped_phase, len, filtered_breathing);
    fir_filter(heart_b, FILTER_ORDER, unwrapped_phase, len, filtered_heart);
    
    ifx_Float_t* bp_in = (ifx_Float_t*)calloc(FFT_SIZE_VITAL, sizeof(ifx_Float_t));
    ifx_Float_t* heart_in = (ifx_Float_t*)calloc(FFT_SIZE_VITAL, sizeof(ifx_Float_t));

    for (i = 0; i < len; i++) {
        bp_in[i] = filtered_breathing[i];
        heart_in[i] = filtered_heart[i];
    }
    
    ifx_Complex_t* bp_fft = (ifx_Complex_t*)malloc(sizeof(ifx_Complex_t) * (FFT_SIZE_VITAL/2 + 1));
    ifx_Complex_t* heart_fft = (ifx_Complex_t*)malloc(sizeof(ifx_Complex_t) * (FFT_SIZE_VITAL/2 + 1));
  
    ifx_FFT_t* bp_inst = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_VITAL);
    ifx_FFT_t* heart_inst = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_VITAL);
    //printf("HERE FISHY FISHY (SEG FAULT FINDER V)\n");
    
    //These two lines seg fault. I think its because the FFT isnt being created. Because its not a power of two
    ifx_fft_raw_rc(bp_inst, bp_in, bp_fft);
    ifx_fft_raw_rc(heart_inst, heart_in, heart_fft);
    /////////////
    int bp_peak_index = 0, heart_peak_index = 0;
    ifx_Float_t bp_max = 0.0, heart_max = 0.0;
    int fft_bins = FFT_SIZE_VITAL/2 + 1;
   //////// printf("HERE FISHY FISHY (SEG FAULT FINDER V)\n");
    for (i = 0; i < fft_bins; i++) {
        ifx_Float_t mag_bp = sqrt(IFX_COMPLEX_REAL(bp_fft[i]) * IFX_COMPLEX_REAL(bp_fft[i]) +
                             IFX_COMPLEX_IMAG(bp_fft[i]) * IFX_COMPLEX_IMAG(bp_fft[i]));
        ifx_Float_t mag_hr = sqrt(IFX_COMPLEX_REAL(heart_fft[i]) * IFX_COMPLEX_REAL(heart_fft[i]) +
                             IFX_COMPLEX_IMAG(heart_fft[i]) * IFX_COMPLEX_IMAG(heart_fft[i]));
        if (mag_bp > bp_max) {
            bp_max = mag_bp;
            bp_peak_index = i;
        }
        if (mag_hr > heart_max) {
            heart_max = mag_hr;
            heart_peak_index = i;
        }
    }
    
    double freq_resolution = VITAL_SIG_SAMPLE_RATE / (double)FFT_SIZE_VITAL;
    double breathing_rate_hz = bp_peak_index * freq_resolution;
    double heart_rate_hz = heart_peak_index * freq_resolution;
    double breathing_rate_bpm = breathing_rate_hz * 60.0;
    double heart_rate_bpm = heart_rate_hz * 60.0;
    printf("PROCESS VITALS ITERATION: %d ", processNum);
    printf("Estimated Breathing Rate: %.2f bpm\n", breathing_rate_bpm);
    printf("Estimated Heart Rate: %.2f bpm\n", heart_rate_bpm);
    
    ifx_fft_destroy(bp_inst);
    ifx_fft_destroy(heart_inst);
    free(bp_fft);
    free(heart_fft);
    free(bp_in);
    free(heart_in);
    processNum++;
}

typedef struct {
    int dummy;
} RadarDataProcessor;

void calc_range_fft(const RadarDataProcessor* processor, ifx_Cube_R_t* frame, ifx_Complex_t* out) {
	
    // Retrieve dimensions from the frame (assumes the frame has a dims[] array)
    int num_rx = NUM_RX_ANTENNAS; //frame->dims[0];
    int num_chirps = NUMBER_OF_CHIRPS; //frame->dims[1];
    int num_samples = SAMPLES_PER_CHIRP; //frame->dims[2];
    int fft_len = SAMPLES_PER_CHIRP;//num_samples * 2;  // fft_size_range_profile (assume it equals 2 * num_samples)
    int out_len = fft_len / 2;      // Only first half (excluding DC symmetries)

    // Initialize output buffer to zeros.
    for (int bin = 0; bin < out_len; bin++) {
        out[bin].data[0] = 0.0;
        out[bin].data[1] = 0.0;
    }
    //////////////////////////////////////////------------------------------

    // Process each antenna and accumulate its FFT result.
    for (int ant = 0; ant < num_rx; ant++) {
        // Allocate a temporary buffer for summing FFT results across chirps for this antenna.
        ifx_Complex_t* ant_fft_sum = (ifx_Complex_t*)calloc(out_len, sizeof(ifx_Complex_t));
        if (!ant_fft_sum) {
            fprintf(stderr, "Memory allocation error for ant_fft_sum.\n");
            return;
        }
        // For each chirp of this antenna:
        for (int chirp = 0; chirp < num_chirps; chirp++) {
            // Get pointer to the data for this chirp. We assume frame->data[ant] 
            // is an array of pointers to sample arrays.
            //ifx_Float_t* chirp_data = frame->data[ant][chirp];
            ifx_Float_t* chirp_data = frame->data + (ant * num_chirps * num_samples) + (chirp * num_samples);

            // Remove DC offset: compute average of the chirp samples.
            double sum = 0.0;
            for (int s = 0; s < num_samples; s++) {
                sum += chirp_data[s];
            }
            double avg = sum / num_samples;
            // Create a temporary signal buffer with DC offset removed.
            ifx_Float_t* signal = (ifx_Float_t*)malloc(fft_len * sizeof(ifx_Float_t));
            if (!signal) {
                fprintf(stderr, "Memory allocation error for signal buffer.\n");
                free(ant_fft_sum);
                return;
            }
            // Also apply Blackman–Harris window; compute window coefficients.
            // The Blackman–Harris window coefficients (for example) are:
            // w[n] = 0.35875 - 0.48829*cos(2*pi*n/(N-1)) + 0.14128*cos(4*pi*n/(N-1)) - 0.01168*cos(6*pi*n/(N-1))
            for (int s = 0; s < num_samples; s++) {
                double window = 0.35875
                                - 0.48829 * cos((2 * M_PI * s) / (num_samples - 1))
                                + 0.14128 * cos((4 * M_PI * s) / (num_samples - 1))
                                - 0.01168 * cos((6 * M_PI * s) / (num_samples - 1));
                signal[s] = (chirp_data[s] - avg) * window;
            }
            // Zero-pad the rest of the signal buffer.
            for (int s = num_samples; s < fft_len; s++) {
                signal[s] = 0.0;
            }

            // Allocate FFT output for a real-to-complex FFT.
            int fft_out_len = fft_len/2 + 1;
            ifx_Complex_t* fft_out = (ifx_Complex_t*)malloc(fft_out_len * sizeof(ifx_Complex_t));
            if (!fft_out) {
                fprintf(stderr, "Memory allocation error for FFT output.\n");
                free(signal);
                free(ant_fft_sum);
                return;
            }
				
            // Create an FFT instance (assuming the SDK provides ifx_fft_create)
            ifx_FFT_t* fft_inst = ifx_fft_create(IFX_FFT_TYPE_R2C, (int)fft_len);
           
            if (!fft_inst) {
                fprintf(stderr, "Failed to create FFT instance.\n");
                free(signal);
                free(fft_out);
                free(ant_fft_sum);
                return;
            }
			
            // Compute FFT for this chirp.
            ifx_fft_raw_rc(fft_inst, signal, fft_out);
            ifx_fft_destroy(fft_inst);
            free(signal);
 				
            // Scale the FFT output: divide by num_samples and multiply results by 2.
            // (Note: In the Python code, FFT result is divided by num_samples and multiplied by 2.)
            for (int bin = 0; bin < out_len; bin++) {
                fft_out[bin].data[0] = fft_out[bin].data[0] / num_samples * 2.0;
                fft_out[bin].data[1] = fft_out[bin].data[1] / num_samples * 2.0;
            }
            // Sum the FFT results from this chirp into ant_fft_sum.
            for (int bin = 0; bin < out_len; bin++) {
                ant_fft_sum[bin].data[0] += fft_out[bin].data[0];
                ant_fft_sum[bin].data[1] += fft_out[bin].data[1];
            }
            free(fft_out);
        } // End of chirp loop

        // Add the antenna’s summed FFT result into the overall output.
        for (int bin = 0; bin < out_len; bin++) {
            out[bin].data[0] += ant_fft_sum[bin].data[0];
            out[bin].data[1] += ant_fft_sum[bin].data[1];
        }
        free(ant_fft_sum);
    } // End of antenna loop

    // Finally, average out by dividing by the number of antennas.
    for (int bin = 0; bin < out_len; bin++) {
        out[bin].data[0] /= num_rx;
        out[bin].data[1] /= num_rx;
    }
}

void process_frame(RadarDataProcessor* processor, ifx_Cube_R_t* frame, double max_range) {
	// printf("Wheres my seg fault? (%d) \n", segFaultFinder++);
	 ifx_Complex_t range_fft_arr[(int)SAMPLES_PER_CHIRP];//FRAME_RATE];
    ifx_Complex_t* range_fft = range_fft_arr;
	  
    calc_range_fft(processor, frame, range_fft);
    if (range_fft != NULL) {
        int start_index_range = (int)(OBJECT_DIST_START / max_range * (FFT_SIZE_RANGE_PROFILE/2));
        int stop_index_range  = (int)(OBJECT_DIST_STOP / max_range * (FFT_SIZE_RANGE_PROFILE/2));
        int range_bin = start_index_range;
        double max_val = 0.0;
        for (int i = start_index_range; i < stop_index_range; i++) {
            double mag = ifx_complex_abs(range_fft[i]);
            if (mag > max_val) {
                max_val = mag;
                range_bin = i;
            }
        }
        
        double wrapped_phase = atan2(IFX_COMPLEX_IMAG(range_fft[range_bin]), IFX_COMPLEX_REAL(range_fft[range_bin]));
        if (phase_index < PHASE_BUFFER_SIZE) {
            phase_buffer[phase_index++] = wrapped_phase;
        }
        if (phase_index >= PHASE_BUFFER_SIZE) { 
            //printf("wheres my segfault VONE MILLION-------------------\n");
            process_vital_signs(phase_buffer, PHASE_BUFFER_SIZE);
            phase_index = 0;
        }
        //free(range_fft);//Seg fauling Not dynamically allocated, doesnt need to be freed.
    }
    
}

int main() {
    RadarDataProcessor radar_processor = {0};

    // Create radar device instance
    ifx_Avian_Device_t* device = ifx_avian_create();
    if (device == NULL) {
        fprintf(stderr, "Failed to create radar device: %s\n", ifx_error_to_string(ifx_error_get()));
        return -1;
    }

    // Print SDK version and device information
    printf("Radar SDK Version: %s\n", ifx_sdk_get_version_string_full());
    printf("UUID of board: %s\n", ifx_avian_get_board_uuid(device));
    printf("Sensor: %u\n", ifx_avian_get_sensor_type(device));

    // Create radar device configuration
    ifx_Avian_Config_t device_config;
    ifx_avian_get_config_defaults(device, &device_config);

    // Customize radar configuration parameters
    device_config.sample_rate_Hz = 4e6;
    device_config.rx_mask = 1;
    device_config.tx_mask = 1;
    device_config.tx_power_level = 31;
    device_config.if_gain_dB = 33;
    device_config.start_frequency_Hz = 57.4e9; // 57.4 GHz
    device_config.end_frequency_Hz = 63.0e9;   // 63 GHz
    device_config.num_samples_per_chirp = SAMPLES_PER_CHIRP;
    device_config.num_chirps_per_frame = NUMBER_OF_CHIRPS;
    device_config.chirp_repetition_time_s = 0.001; // 1 ms chirp repetition time
    device_config.frame_repetition_time_s = 1.0 / FRAME_RATE; // Frame rate defined previously

    // Apply the configuration to the radar device
    ifx_avian_set_config(device, &device_config);

    // Check for errors after setting the configuration
    if (ifx_error_get() != IFX_OK) {
        fprintf(stderr, "Failed to configure radar device: %s\n", ifx_error_to_string(ifx_error_get()));
        ifx_avian_destroy(device);
        return -1;
    }

    // Calculate range resolution and maximum range based on sensor configuration
    double chirp_bandwidth = device_config.end_frequency_Hz - device_config.start_frequency_Hz;
    double range_res = (3e8) / (2 * chirp_bandwidth);
    printf("Range resolution: %.3f m\n", range_res);
    
    double max_range = range_res * SAMPLES_PER_CHIRP / 2;
    printf("Maximum range: %.3f m\n", max_range);

    // Main processing loop (no multithreading)
    while (1) {
        // Acquire next frame from radar sensor
        ifx_Cube_R_t* frame = ifx_cube_create_r(NUM_RX_ANTENNAS, NUMBER_OF_CHIRPS, SAMPLES_PER_CHIRP);
        if (frame == NULL) {
            fprintf(stderr, "Failed to create frame structure.\n");
            return -1;
        }
        frame = ifx_avian_get_next_frame(device, NULL);
        if (frame == NULL) {
            fprintf(stderr, "Failed to acquire frame: %s\n", ifx_error_to_string(ifx_error_get()));
            break; 
        }

        // Process the acquired frame data
        process_frame(&radar_processor, frame, max_range);

        // Free the acquired frame after processing
        ifx_cube_destroy_r(frame);

        usleep(1000); // Short delay to limit CPU usage
    }

    // Clean up and release radar resources
    ifx_avian_destroy(device);

    return 0;
}