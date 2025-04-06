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

From the heart rate tests, it is apparent that the device successfully detects heart rate and can semi-accurately describe the actual rate. The present error could exist due to extraneous phase jumps that cause momentary spikes in the derived heart rate; some investigation into these phase jumps is needed to formalize a solution. However, the prototype performs accurately enough as a proof of concept. There is sufficient data to suggest that an increase in heart rate correlates to an increase in measured heart rate. This implies a causal relationship between the measured heart rate and the actual heart rate. Further development needs to be done to increase accuracy in the higher heart beat ranges since a subject with a higher heart rate typically is in more motion (shaking, breathing with intensity) creating more noise that disrupts readings. 

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

The Doppler breathing rate monitor performs well for fast breathing rates above 20 breaths per minute (bpm), showing excellent accuracy with errors between 0-9.5%. However, its reliability drops significantly for slower breathing rates—below 10 bpm, errors skyrocket up to 360%, with severe overestimation (e.g., counting 22 bpm instead of the actual 5 bpm). In the moderate range (10-16 bpm), accuracy is inconsistent, with errors between 12.5-28.6%. These results suggest the system excels at detecting rapid, pronounced breathing but struggles with slow respiration, likely due to interference from heartbeat signals or other noise. While suitable for monitoring during exercise or stress, the technology requires significant improvements for accurate low respiratory measurements. This rate-dependent performance highlights the need for context-specific validation in respiratory monitoring applications.


### Experimental Conclusion

Further investigation is required to determine the cause of the high inaccuracy present in the low breathing ranges. However, the data has a correlation between the actual breathing rate and the measured breathing rate and is able to detect the lack of a breathing rate. This implies the device has a causal relationship between the actual and measured breathing rates. A potential reason for the device's incapability at detecting lower breathing rates is that motion that slow will have a low magnitude, likely lower than what the device is programmed to detect. After the high inaccuracy is investigated and a solution implemented, the experiment needs to be conducted again.

## Video Experiment 

### Video Latency Experiment 
The video latency experiment was designed to measure transmission delay at different distances using WebRTC technology. The getStats function was used to collect latency data directly from the WebRTC connection, giving real-time information about network performance. The experiment included several distance points, from very close to about 110 feet, to see how distance affects video delay. This setup made it possible to compare how latency changed as the devices were moved farther apart. The results were shown in a graph that displayed the connection between distance and latency. The testing was done indoors, with relatively short distances and few obstacles. 

### Expectation 
The expected results were that latency would increase slightly as the distance between devices grew. Since the distances tested were relatively short and WebRTC is designed for low-latency communication, the latency was not expected to go over one second. At shorter distances, the latency was expected to stay mostly consistent, with only small changes as the distance reached up to 110 feet.

### Procedure
  - Step 1: Turn on Jetson Nano and start video streaming application
  - Step 2: Increase the distance between the host device and client device by intervals of 12 feet
  - Step 3: Calculate latency at each 12 foot interval with getStats() function in WebRTC
  - Step 4: Collect data points and show the average trend
  - Step 5: Finished Testing
### Data Analysis 
![output](https://github.com/user-attachments/assets/9023d9f1-9465-47ff-aba8-1805cedccb08)
This graph shows how video latency changes as the distance from the triage system increases. We measured latency at intervals of 12 feet, starting from 0 and going up to 110 feet. Each red dot represents an interval of 12 feet measurement we took during testing, and the blue curve shows the overall trend. At close range, latency was very low—around 0.008 seconds. As we moved farther away, the latency gradually increased, reaching about 0.180 seconds at the maximum distance of our testing site of 110 feet.
