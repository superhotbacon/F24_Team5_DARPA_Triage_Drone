
# Signal Processing Detailed Design


## Function of the Subsystem

The signal processing subsystem's purpose is to take the data gathered from the doppler radar and obtain the heart rate and respiratory rate from the signal. Within the entire drone, the signal processing subsystem serves as a middleman between the programmable drone subsystem and the sensors subsystem. This subsystem will be primarily on a Jetson Nano. The Jetson Nano will be part of the Microphone and Video subsystem, Signal Processing subsystem, and the programmable drone subsystem. Because all of these subsystems will be using the Jetson Nano, it is important that the algorithms used in this subsystem are powerful and computationally efficient. 


## Specifications and Constraints

  (1) The signal processing subsystem SHALL use signal processing to determine heart rate (range 0.45 to 2.92Hz) and respiratory rate (range 0.13 to 1 Hz). This specification stems from the subsystem prerequisites that allow the drone to work as intended.  
  (2) The signal processing subsystem SHALL be able to get accurate readings from 1 meter away. This specification stems from the customer, Georgia Tech Research Institute. This allows the drone to read the vitals of the victim without risking hurting the individual. Or in the possible case that the victim is inaccessible and can only be seen from 1 meter away.  
 (3) The signal processing algorithms SHALL process data and have it ready to transmit within 500ms of being received. This specification stems from prerequisites that ensure the timely display of results so the operators can make quick decisions in high stress situations.   
 (4) The signal processing subsystem SHALL not store heart rate and respiratory rate data in long term storage that persists after power on reset. This constraint stems from ethics as the drone should not be used to sell heart rate and respiration rate data for companies to use to target products or services to patients.  


## Overview of Proposed Solution


Extensive research has gone into the use of doppler radars over the last decade[1]. A lot of this research has been solving multiple issues with contactless monitoring, such as movement artifacts from personal movement, motion artifacts from doppler movement, monitoring multiple people, and more. The two main choices are CW (continuous wave) and FMCW (frequency modulated continuous wave). Continuous wave is not able to find the distance of the object, only the change in distance. While this is suitable for this project, research indicates that FMCW dopplers are able to reduce motion artifacts associated with doppler movement with the addition of an accelerometer to measure this movement [2].


The algorithm the drone will utilize has three parts. Demodulation, Empirical Mode Decomposition (EMD) to eliminate motion artifacts, and finally band pass filtering to extract the two desired frequencies from the reconstructed signal. Furthermore, the distance to the target can also be extracted as the beat frequency of the modulated wave is proportional to the distance [4].


This algorithm will meet the specifications of the subsystem as it effectively removes motion artifacts and extracts the heart beat and respiratory rate. The use of the Jetson Nano will ensure the data is processed and passed onto the next subsystem in the path to the operator.

## Interface with Other Subsystems
The Signal processing subsystem will need to interface to the sensor subsystem as well as the programmable drone. 

To connect to the sensor subsystem, the connection will be established using USB. The data received from the sensor can come in many different forms as the chosen sensor is very robust. The form chosen for the data will be unprocessed. The sensor will pass raw data to the Jetson Nano. This is desirable as the Jetson Nano can fully use the data to  extract all relevant information. If processing time becomes a concern, the team can program the doppler to preprocess the data to a smaller degree than the Jetson Nano. This will reduce the load on the Jetson Nano and decrease processing time.

To connect to the programmable drone the Jetson Nano will need to connect using USB. The data sent to this subsystem will be relevant sensor data such as the Heart rate and the Respiratory rate. This data will need to be put into the specified network packets used by that subsystem, whether that be UDP, TCP, or others.


## Operational Flowchart
<img width="1651" alt="Drawing 12" src="https://github.com/user-attachments/assets/8e0b39fc-ded5-4406-a414-bbeeff075a1c">



## BOM

A complete list of all components needed for the design must be given with the cost of each component and the total cost of the subsystem. The BOM should be a markdown table. Make sure to to provide the manufacteror, part number, distributor, distributor part number, quantity, and price. Also provide a url where the product can be purchased from. If the componenet is refernced on your schematic make sure to include the component name.

| PART NUMBER            | DESCRIPTION     | MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:    | :---:         | :---:                  |
 J1020 V2               | [Jetson Nano Developer Kit](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html) | Nvidia | 1 | $279.00 | $279.00 |
| ADXL203EB              | [Dual Axis Accelerometer](https://www.digikey.ee/en/products/detail/analog-devices-inc/ADXL203EB/665382) | Analog Devices | 1 | $56.59 | $56.59 |
|                        |                                                                                                |                                  |   | **Total Expenses** | **$335.59** |
|                        |                                                                                                |                                  |   | **Total Quantity** | **2** | 
## Analysis

The previous research into removing unwanted doppler movement [2] had motion artifacts in a similar range to the desired measurable range. However, for the drone, movement artifact frequencies are expected to be >80 Hz [4]. For the heart rate and respiration rate the desired frequencies are <10 Hz. These are two extremely different frequency bands. While a low pass filter can filter out this noise, it may not be effective enough as the surface vibrations are not stationary in the frequency band and could possibly fall into the range the drone aims to measure. Furthermore, the difference in amplitude between the respiration rate and the heart rate can pose problems to deconstruct the signal into separate Intrinsic Mode Functions (IMF) [2] explained next.

EMD works well to solve the problem of motion artifacts. EMD is an empirical method that works well for signals that are either non linear or non stationary [5]. This makes EMD a great choice for contactless health systems monitoring. Part of the EMD process is splitting up the input signal into Intrinsic Mode Functions (IMF). These IMFs must satisfy two conditions:

`(1) in the whole data set, the number of extrema and the number of zero crossings must either equal or diﬀer at most by one; and (2) at any point, the mean value of the envelope deﬁned by the local maxima and the envelope deﬁned by the local minima is zero.[5]`

This effectively splits up the input signal into different components that share similar properties. This allows for quantitative and qualitative analysis of the parts of a signal [2]. This solves both issues stated above. After separating the signal into its IMF components, the unwanted noise can be analyzed, removed, and the signal reconstructed. The heart rate can then be extracted from this reconstructed signal

In order to determine what IMFs contain the motion artifact, an accelerometer should be used to determine the x and y position of the doppler radar during measurement. Using the accelerometer allows for quantitative correlation between each IMF and the artifact signal[2]. This can be used to determine which IMFs to cut out when reconstructing the signal.

To solve the issue of heart respiration causing problems using EMD, a high pass filter can be used to attenuate the respiration signal [2]. The respiration rate can still be obtained by copying the input data into another dataset  and preforming a low pass filter on that set. 

This analysis explains why the proposed algorithm will work to extract both the heart rate and respiratory rate. This will satisfy the subsystems specifications (1) and (2). 

Due to the computationally heavy EMD approach, a powerful system will be needed to achieve the timing specifications. After researching the topic, the Jetson Nano is considered the best option as it is a System on Module (SOM) that runs Linux and a GPU that will perform well with our algorithm. An operating system is absolutely required because the Jetson Nano will have to communicate with the sensors, speakers, microphones, cameras, and the programmable drone. The operating system will handle the context switching required to run all of these functions. This device will help satisfy the (3) specification.


## References

[1] C. Gu, “Short-Range Noncontact Sensors for Healthcare and Other Emerging Applications: A Review,”  _Sensors_, vol. 16, no. 8, p. 1169, Jul. 2016, doi: https://doi.org/10.3390/s16081169.

[2] I. Mostafanezhad, E. Yavari, O. Boric-Lubecke, V. M. Lubecke, and D. P. Mandic, “Cancellation of Unwanted Doppler Radar Sensor Motion Using Empirical Mode Decomposition,”  _IEEE Sensors Journal_, vol. 13, no. 5, pp. 1897–1904, May 2013, doi: https://doi.org/10.1109/jsen.2013.2238376.

‌‌[3] G. M. Brooker, “Understanding Millimetre Wave FMCW Radars ,” Nov. 21, 2005. https://www.researchgate.net/profile/Graham-Brooker/publication/228979037_Understanding_millimetre_wave_FMCW_radars/links/02e7e514a21ca686df000000/Understanding-millimetre-wave-FMCW-radars.pdf (accessed Nov. 25, 2024).

‌[4] J. Verbeke and S. Debruyne, “Vibration analysis of a UAV multirotor frame.” Available: https://past.isma-isaac.be/downloads/isma2016/papers/isma2016_0797.pdf

‌[5] N. E. Huang  _et al._, “The empirical mode decomposition and the Hilbert spectrum for nonlinear and non-stationary time series analysis,”  _Proceedings of the Royal Society of London. Series A: Mathematical, Physical and Engineering Sciences_, vol. 454, no. 1971, pp. 903–995, Mar. 1998, doi: https://doi.org/10.1098/rspa.1998.0193.

‌
