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

The Doppler heart rate monitor performs well for normal resting heart rates between 60-100 beats per minute (bpm), with about 69% of readings falling within 10% of the correct value and perfect accuracy at certain rates like 61, 70, 75, and 82 bpm. However, its reliability drops significantly for elevated heart rates above 100 bpm, where errors average nearly 48% and can skyrocket to 73-82% in cases of extreme tachycardia. The system also struggles with rapid heart rate changes, high variability, and specific ranges around 70 and 85 bpm, suggesting limitations in processing fast or irregular signals. While suitable for routine monitoring at rest, these flaws—especially the worsening accuracy at higher heart rates—highlight the need for improved motion artifact filtering and better high-rate detection before the device can be trusted in high-stress or exercise conditions.


### Expermintal Conclusion


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

The Doppler breathing rate monitor performs well for fast breathing rates above 20 breaths per minute (bpm), showing excellent accuracy with errors between 0-9.5%. However, its reliability drops significantly for slower breathing rates—below 10 bpm, errors skyrocket up to 360%, with severe overestimation (e.g., counting 22 bpm instead of the actual 5 bpm). In the moderate range (10-16 bpm), accuracy is inconsistent, with errors between 12.5-28.6%. These results suggest the system excels at detecting rapid, pronounced breathing but struggles with slow respiration, likely due to interference from heartbeat signals or other noise. While suitable for monitoring during exercise or stress, the technology requires significant improvements for accurate resting respiratory measurements. This rate-dependent performance highlights the need for context-specific validation in respiratory monitoring applications.


### Experimental Conclusion



