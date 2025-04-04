## Introduction 

After much designing, coding, and building, our group is ready to evaluate the prototype that will act as a proof of concept for our project. There are multiple facets to the device, so multiple tests will be required to prove the device meets the desired specifications.


## Purpose of the Experiments


The experiments will be conducted to ensure that the following four functions of the device are operational:
  
**1.** Heart Rate Measurement.  
>It's crucial that the estimate the device produces for a subject's heart rate is reasonably similar to the subject's actual heart rate. Our experiment is meant to ensure the device is sending accurate results. 
    
**2.** Breath Rate Measurement.  
>Just like the heart rate measurement, the device must generate accurate breathing rate predictions. The tests we run will certify proper function.

**3.** Video Interface.  
>Since the operator of the device will not be present when the device locates a subject, video interface will allow the operator to determine the immediate state of a subject. The video interface needs to function at farther ranges to prove useful with relatively clear display. Our tests will aim to ensure this is the case.

**4.** Audio Interface.
>To communicate with a subject, the operator will require an audio interface. This test will verify that the operator can communicate with a subject and vice versa from a reasonable distance.

## Experiments for Heart Rate

This experiment was designed to capture a variety of heart rates across different participants. By utilizing multiple volunteers, the study incorporated natural variations in heart rate responses. The testing protocol enabled six distinct data comparisons per trial, providing a robust dataset for analysis. This approach allowed researchers to gather sufficient evidence to draw meaningful conclusions about measurement accuracy. In this experiment, we wanted to test the reliability and the accuracy of the heart rate measurements. In setting up the experiment, we needed the Doppler, Jetson Nano, and a heart rate monitor. Next, we took the volunteers to lie under the Doppler a meter away and also attached the heart rate monitor to their finger. We had the volunteers lie under the Doppler for one minute while recording both the Doppler's and the heart rate monitor's readings every 10 seconds.

### Expectation
In the experiment, it is expected that we will find the Doppler's measurements will match the heart rate monitor's measurements. This will prove that the Doppler can provide accurate and repeatable measurements for the heart rate.

### Procedure
  - Step 1: Turn on Jetson nano and start the Doppler Program
  - Step 2: Have volunteer lay down under doppler
  - Step 3: Attach heart rate moniture to the volunteer
  - Step 4: Start timer
  - Step 5: Every 10 seconds record the dopplers measurement and the heart rate moniture's measurement.
  - Step 6: Once timer is up the test is finished
  
### Data Analysis

![image](https://github.com/user-attachments/assets/b8d21bb7-6670-4605-bf81-73fc719b6965)

The heart rate measurement analysis reveals the Doppler system demonstrates good reliability for normal resting rates (60-100 bpm), with 68.9% of measurements showing ≤10% error in this range, including perfect agreement at several points (61, 70.3, 75 and 82 bpm). However, performance degrades significantly at elevated heart rates (>100 bpm), where errors become substantially larger (average 47.6% error) and more variable, reaching extreme inaccuracies of 73-82% in tachycardic states. The system shows particular difficulty handling high heart rate variability, abrupt rate changes, and very specific rate ranges around 70 bpm and 85 bpm, suggesting limitations in signal processing during physiological extremes. While demonstrating promise for routine resting patient monitoring, these findings indicate the need for technical improvements in high-rate detection algorithms, motion artifact rejection, and adaptive filtering for tachycardia before the system could be considered reliable for comprehensive clinical use, particularly in high-stress or exercise conditions where elevated heart rates are expected. The consistent pattern of deteriorating accuracy with increasing heart rate suggests fundamental challenges in the Doppler's ability to process rapid cardiac signals without aliasing or interference artifacts.


### Expermintal Conclusion
The experimental data reveals fundamental challenges in the Doppler system's ability to accurately measure physiological signals across different physiological states. For breathing rate detection, the system's performance degrades significantly at lower respiratory rates (4-7 breaths/min), where measurement errors escalate to 77-360%. This pattern strongly suggests the system struggles to distinguish true respiratory movements from other low-frequency physiological noise when thoracic displacement amplitudes are minimal.

## Experiment for Breathing Rate 

The breathing rate experiment was structured to evaluate measurement accuracy across varying respiratory patterns. We collected data from multiple volunteers to incorporate natural variations in breathing rates. The experiment tested three conditions slow, nominal, and fast breathing generating comparative datasets for each respiratory state. This method enabled comprehensive analysis of measurement consistency across different breathing paces. This experiment will have a similar setup to the heart rate experiment, except that the breathing rate will be recorded. This experiment has two parts due to inconclusive data from the first round of testing, which required further investigation. The first part involved volunteers lying down and counting their breaths naturally. The second part was more structured: volunteers were asked to first breathe slowly for one minute, then breathe normally for one minute, and finally breathe quickly for one minute. This approach allowed us to collect low, nominal, and high breathing rate data sets for comparison with the Doppler's readings.

### Expectation
In the experiment, it is expected that we will find the Doppler's measurements will match the the volunteers breath intake count. This will prove that the Doppler can provide accurate and repeatable measurements for the breathing rate.

### Procedure
  - Step 1: Turn on Jetson nano and start the Doppler Program
  - Step 2: Have Volunteer lay down under doppler
  - Step 3: Have Volunteer count every breath intake
  - Step 4: Start timer
  - Step 5: Once timer is reached 1 min record the volunteers breath count and the dopplers recording
  - Step 6: Test is finished

### Data Analysis

![image](https://github.com/user-attachments/assets/c83787d1-e0ff-4c3c-9134-ce8bbba5de74)

The comprehensive breathing rate evaluation, including both controlled-rate experiments and broader sample analysis, reveals distinct performance patterns in the Doppler measurement system. When testing controlled rates (low: 5 bpm, nominal: 11 bpm, high: 25 bpm), the system showed severe overestimation at low rates (22 bpm vs 5 bpm counted, 77.27% error), moderate inaccuracy at normal rates (14 bpm vs 11 bpm, 21.43% error), and perfect accuracy at high rates (0% error). This pattern was corroborated in expanded testing, where performance deteriorated dramatically below 10 breaths/min (errors up to 360%) but achieved excellent reliability above 20 breaths/min (0-9.52% error). The transition zone (10-16 bpm) showed intermediate accuracy (12.50-28.57% error), suggesting the system's capabilities are strongly rate-dependent. These consistent findings indicate the technology excels at detecting pronounced, frequent breathing motions while fundamentally struggling with slow respiration, likely due to interference from cardiac signals or other physiological noise. The results strongly suggest that while the system may be suitable for monitoring elevated respiratory rates during exercise or physiological stress, significant algorithmic improvements are needed for reliable resting respiratory measurement applications. This rate-dependent performance characteristic highlights the importance of context-specific validation for respiratory monitoring technologies.


### Expermintal Conclusion

The experimental data reveals fundamental challenges in the Doppler system's ability to accurately measure physiological signals across different physiological states. For breathing rate detection, the system's performance degrades significantly at lower respiratory rates (4-7 breaths/min), where measurement errors escalate to 77-360%. This pattern strongly suggests the system struggles to distinguish true respiratory movements from other low-frequency physiological noise when thoracic displacement amplitudes are minimal.

