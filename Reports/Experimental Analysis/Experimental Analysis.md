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
This graph shows how video latency changes as the distance from the triage system increases. We measured latency at intervals of 12 feet, starting from 0 and going up to 110 feet. Each red dot represents an interval of 12 feet measurements took during testing, and the blue curve shows the overall trend. At close range, latency was very low—around 0.008 seconds. As the client device moved farther away, the latency gradually increased, reaching about 0.180 seconds at the maximum distance of our testing site of 110 feet.  
  
    
  ![test from vent](https://github.com/user-attachments/assets/a892816b-a52a-44b3-bbfc-4b1f5bc8c684)
The image shows an example test at the maximum distance of 110 feet, where the video stream maintained a consistent latency of around 177 milliseconds and a stable frame rate of about 30 FPS. The connection remained reliable throughout the test.

### Video Quality Experiment
In this experiment we used a running clock to be able to observe the choppiness of the transmitted video as well as to read the frames per second. Just like the latency test, the video quality was observed at incresing distances. The experiment was ran indoors without any obstacles to obstruct the signal between the client and host devices. This setup made it possible to observe if the video quality at different distances will be detremental to the trage drones functionality. 

### Expectations
In this experiment it is expected that the video quality will maintain excellence (roughly 30 FPS) as the distance increases to a testing max of 110 feet. This will prove that the video will clearly display the timer's digits used for the experiment. 

### Procedure 
- Step 1: Turn on Jetson Nano and start video streaming application
- Step 2: Increase the distance between the host device and client device by intervals of 12 feet
- Step 3: Calculate frames per second at each 12 foot interval with getStats() function in WebRTC
- Step 4: Observe clear whether output is clear and timer is readable
- Step 5: Finish Testing
  

### Data Analysis
| Distance (ft)        | Signal Quality  |  Video Quality     | Frames Per Second |
| :----                | :----:          |  :----:           | :-----:   |                
| 12                   | Excellent       | Good              |  30  |      
| 40                   | Excellent       | Good              |  30  |   
| 80                   | Excellent       | Good              |  30  |   
| 90                   | Excellent       | Good              |  30  |    
| 110                  | Excellent       | Good              |  29  |    

The video quality stayed the same during the entire test, even as the distance between devices increased to 110 feet. There were no changes in how sharp, smooth, or clear the video looked. The stream stayed steady, with no lag, blurriness, or skipped frames. This shows that the system kept a strong and reliable video connection at all distances tested indoors without any obstructions.   

![video quality at 110](https://github.com/user-attachments/assets/d31f4d93-3303-430b-b7c5-b582ef702720)
This image shows a video quality test at 110 feet, demonstrating a stable video stream at 29 FPS with a readable timer of 1:06.37 seconds.

### Video Conclusion
The video tests showed that the system worked well at all distances up to 110 feet. The delay increased slightly as the distance grew, starting at about 0.008 seconds and reaching around 0.180 seconds, but it stayed low the whole time. The video quality stayed the same during the test, with a steady frame rate of about 30 FPS and no lag, blurriness, or skipped frames. This shows that the video stream stayed clear and stable across all distances in the indoor test.

### Audio Quality Experiment
In this experiment, one person was used as the "victim" at the drone end of the speaker. This person listened for 5 phrases comming from the operator (PC) end of the system. Then the victim will respond to each prompt that comes from the operator. This test was ran at the max testing distance of 110 feet without any obstructions to interfere with the connection siganl. This experiment will prove that a person in need will be able to hear prompts coming from the drone operator. It will also prove that the victim will be able to communicate needs back to the first responder. 

### Expectations
In this experiement it is expected that the test subject will be able to accuratly depict the phrases communicated from the operator device. It is also expected that the operator will be able to clearly understand the test subject responding to the previously given prompts. \

### Procedure 
- Step 1: Turn on Jetson Nano and start video streaming application
- Step 2: Test subject listens for operator's prompts and writes them down
- Step 3: Operator listens for subjectes responses and writes them down.
- Step 4: Verify that the prompts and responses were recieved accuratley.
- Step 5: Finish Testing

### Data Analysis 

### Audio Conclusion
The tests showed that both the video and audio transmission remained clear and reliable across all distances up to 110 feet. The video maintained a steady frame rate of around 30 FPS with no visible lag, blurring, or frame drops, even at the farthest point. Audio quality was also consistent, with no noticeable delays, dropouts, or distortion. In the audio test, both participants were able to clearly hear each other and respond to spoken prompts without issues. Overall, the system provided smooth video and audio communication with low latency and stable performance throughout each test. These experiments were limited to indoor tests due to only having a minimal functioning prototype without an external power source. The maximum range was 110 feet. 


### Satements of Contribution
-Gabe, Mathias, Caleb: Conducted the experiments for the heart rate and breathing rate. Also, put together the analysis report for both experiments. 
-Reese, Chris: Conducted the experiments for the video and audio. Also, put together the analysis report for both video and audio. 


