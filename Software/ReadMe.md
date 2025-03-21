This README is specific to the BGT60U_maybe.c file.


---

### **Explanation of the Code**

The provided code demonstrates how to use Infineon's BGT60U radar sensor to detect vital signs, specifically **breathing rate** and **heart rate**, by processing radar phase data. Below is a detailed explanation of how the code works and the variables that can be modified for different contexts.

---

### **How the Code Works**

#### **1. Initialization**

- The radar device is initialized using Infineon's Radar SDK (`ifx_avian_create()`).
- Default configuration parameters are retrieved using `ifx_avian_get_config_defaults()` and customized for the application.
- The configuration is applied to the radar device using `ifx_avian_set_config()`.


#### **2. Frame Acquisition**

- Radar frames are continuously acquired in the main processing loop using `ifx_avian_get_next_frame()`.
- Each frame contains raw radar data represented as a 3D data cube (`ifx_Cube_R_t`).


#### **3. Range FFT and Phase Extraction**

- A range FFT is computed using `calc_range_fft()` to identify the range bin corresponding to the target.
- A specific range bin is selected based on the target distance (`OBJECT_DIST_START` to `OBJECT_DIST_STOP`).
- Phase information is extracted from the selected range bin.


#### **4. Signal Processing**

- The extracted phase is unwrapped using `unwrap_phase()` to remove discontinuities caused by its periodic nature.
- Bandpass FIR filters (`fir_filter()`) are applied to isolate breathing and heart rate signals from the unwrapped phase data.


#### **5. FFT Analysis**

- FFTs are computed for both filtered signals using Infineon's FFT API (`ifx_fft_raw_rc()`).
- The dominant frequency components in the FFT results are identified:
    - Low-frequency components correspond to **breathing rate**.
    - Higher-frequency components correspond to **heart rate**.


#### **6. Vital Sign Estimation**

- The dominant frequencies are converted into beats per minute (bpm) using:

$$
\text{rate\_bpm} = \text{rate\_hz} \times 60
$$
- The estimated breathing rate and heart rate are printed to the console.

---

### **Key Variables**

#### **Radar Configuration Variables**

These variables define how the radar operates:

1. **`device_config.start_frequency_Hz` and `device_config.end_frequency_Hz`**:
    - Define the frequency range of the radar chirp, which affects range resolution.
    - Larger bandwidth (difference between `end_frequency_Hz` and `start_frequency_Hz`) results in finer range resolution.
2. **`device_config.sample_rate_Hz`**:
    - Defines the sampling rate of the radar ADC.
    - Higher sampling rates allow larger maximum ranges but may require more processing power.
3. **`device_config.num_samples_per_chirp`**:
    - Defines how many samples are collected per chirp.
    - Affects both maximum range and range resolution.
4. **`device_config.num_chirps_per_frame`**:
    - Defines how many chirps are collected per frame.
    - More chirps improve signal quality but increase processing time.
5. **`FRAME_RATE`**:
    - Defines how often frames are acquired (in Hz).
    - Higher frame rates provide faster updates but may reduce signal-to-noise ratio (SNR).

---

#### **Signal Processing Variables**

These variables control how signals are processed:

1. **Range Selection (`OBJECT_DIST_START`, `OBJECT_DIST_STOP`)**:
    - Define the physical distance range (in meters) of interest.
    - Only signals within this range are processed.
2. **FIR Filter Parameters (`LOW_BREATHING`, `HIGH_BREATHING`, `LOW_HEART`, `HIGH_HEART`)**:
    - Define the frequency ranges for breathing and heart rate signals (in Hz).
    - These values should be adjusted based on expected vital sign ranges for your application.
3. **FFT Parameters (`FFT_SIZE_VITAL`)**:
    - Defines the size of the FFT applied to filtered signals.
    - Larger FFT sizes provide finer frequency resolution but require more computation.
4. **Phase Buffer Size (`PHASE_BUFFER_SIZE`)**:
    - Defines how many phase samples are buffered before processing.
    - Larger buffers improve frequency resolution but increase latency.

---

### **Customizable Variables for Different Contexts**

#### **1. Adjusting Range of Interest**

Modify these variables to process signals from a specific distance range:

```c
#define OBJECT_DIST_START 0.5  // Minimum distance in meters
#define OBJECT_DIST_STOP 0.6   // Maximum distance in meters
```


#### **2. Filtering Frequency Ranges**

Update these variables based on expected breathing and heart rate ranges:

```c
#define LOW_BREATHING 0.15     // Minimum breathing frequency in Hz
#define HIGH_BREATHING 0.6     // Maximum breathing frequency in Hz
#define LOW_HEART 0.85         // Minimum heart frequency in Hz
#define HIGH_HEART 2.4         // Maximum heart frequency in Hz
```


#### **3. Radar Sampling Parameters**

Modify these variables for different resolutions or ranges:

```c
#define SAMPLES_PER_CHIRP 64   // Number of samples per chirp
#define NUMBER_OF_CHIRPS 1     // Number of chirps per frame
```


#### **4. Frame Rate**

Adjust this variable for faster updates or higher SNR:

```c
#define FRAME_RATE 20.0        // Frame acquisition rate in Hz
```

---

### **How It Can Be Modified for Different Contexts**

1. **Shorter or Longer Range Detection**:
    - Change `OBJECT_DIST_START` and `OBJECT_DIST_STOP` to detect targets at different distances.
    - Increase radar bandwidth (`end_frequency_Hz - start_frequency_Hz`) for finer resolution.
2. **Different Vital Sign Ranges**:
    - Modify `LOW_BREATHING`, `HIGH_BREATHING`, `LOW_HEART`, and `HIGH_HEART` to match expected vital sign frequencies for different subjects or conditions.
3. **Higher Resolution or Faster Updates**:
    - Increase `SAMPLES_PER_CHIRP` for finer range resolution.
    - Increase `FRAME_RATE` for faster updates, but ensure processing time does not exceed frame interval.
4. **Noise Reduction**:
    - Implement additional filtering or denoising techniques (e.g., moving average or wavelet transforms).

---

### Summary

The code processes radar data from Infineon's BGT60U sensor to estimate breathing and heart rates by analyzing phase information within a specific range of interest. It uses FIR filters, FFT analysis, and customizable parameters for signal processing, making it adaptable to various contexts such as healthcare monitoring or presence detection.

By modifying key variables like range selection, filter parameters, sampling rates, and frame rates, this code can be tailored for different applications or environments requiring vital sign detection with radar technology.

<div style="text-align: center">⁂</div>

[^1]: https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/55565756/9547f69b-f387-412e-9e07-485fab7ebc0e/BGT60U_maybe.c
