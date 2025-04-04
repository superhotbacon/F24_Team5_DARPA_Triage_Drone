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
![image](https://github.com/user-attachments/assets/6db1cb2f-f15b-4d7d-92a3-7b168485280b)
![image](https://github.com/user-attachments/assets/7d5fd322-9df0-405a-9775-956546fbb93f)
![image](https://github.com/user-attachments/assets/303072b5-7110-4e35-9d48-3089ac9fd7e1)

The data reveals that the Doppler system generally aligns well with the heart rate monitor in Tests 1, 2, and 4, showing average errors between 0.43% and 2.97%, indicating reasonable agreement. However, in Test 3, the Doppler underestimated heart rates by 7.47%, and in Test 5, the discrepancy widened to 10.09%, with extreme single-point errors reaching 25–26% during the final seconds. Test 4 demonstrated the most stability, with a near-perfect match at 30 seconds (0% error) and a maximum error of just 9.88%, while Test 5’s inconsistencies suggest challenges with higher heart rates or motion artifacts. Potential error sources include sensor misalignment, physiological fluctuations, or Doppler’s lag in tracking rapid heart rate changes.

### Expermintal Conclusion

## Experiment for Breathing Rate 

The breathing rate experiment was structured to evaluate measurement accuracy across varying respiratory patterns. Researchers collected data from multiple volunteers to incorporate natural variations in breathing rates. The experiment tested three conditions slow, nominal, and fast breathing generating comparative datasets for each respiratory state. This method enabled comprehensive analysis of measurement consistency across different breathing paces. This experiment will have a similar setup to the heart rate experiment, except that the breathing rate will be recorded. This experiment has two parts due to inconclusive data from the first round of testing, which required further investigation. The first part involved volunteers lying down and counting their breaths naturally. The second part was more structured: volunteers were asked to first breathe slowly for one minute, then breathe normally for one minute, and finally breathe quickly for one minute. This approach allowed us to collect low, nominal, and high breathing rate data sets for comparison with the Doppler's readings.

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
![image](https://github.com/user-attachments/assets/a2a0ec20-c11f-4aeb-829f-3e9fdf431a44)

This data taken was inconclusive on accuracy and needed further more indepth testing to understand the inaccuracy of the doppler.

![image](https://github.com/user-attachments/assets/79a64059-3ea9-4a55-bec3-d78a8edce9bf)

After conducting the second experiment with controlled breathing rates (low: 5 bpm, nominal: 11 bpm, high: 25 bpm), clear patterns emerged in the Doppler system's performance. At the low breathing rate, the Doppler significantly overestimated breaths (22 bpm vs counted 5 bpm, 77.27% error). The Performance improved at nominal rates, though still showed some error (14 bpm vs 11 bpm, 21.43% error). Most notably, the system achieved perfect accuracy (0% error) at high breathing rates, suggesting it works best with pronounced, frequent breathing motions that generate clearer signals. These results demonstrate that the Doppler's reliability increases with breathing frequency, performing excellently at elevated rates while struggling with false positives during slow breathing and showing intermediate accuracy at normal respiratory rates.

### Expermintal Conclusion

