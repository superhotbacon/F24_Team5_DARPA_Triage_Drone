# Interfacing Detailed Design
This document delineates a fully comprehensive system design for the interfacing subsystem. Focusing on the integration within the broader solution, the specifications and constraints relevant to the interfacing, and the process and justification of each crucial design step that constructs the solution. 


## Interfacing Subsystem Function

The interfacing subsystem will function as the project's wireless data visualization via the use of a compatible laptop device. This involves wirelessly gathering and receiving the processed data from the Jetson Nano computing device attached to the drone and displaying live, engaging data visuals for the user within near-immediate transmission and processing times. Live video and audio from the camera and microphone connected to the drone will be streamed to the laptop, and data from the triage signal processing systems will be displayed wirelessly. 

## Specifications and Constraints

#### Constraints

**1.** The subsystem MUST maintain an error rate of less than 1% to ensure accurate transmitted data display.  
**2.** The subsystem MUST clock a latency of <1 second for video, audio, and data streaming.  
**3.** The subsystem MUST process and display data without storing any of the received data.  
  
**It is important that these constraints are met due to the importance and crucial need for fast accurate data for life-saving measures.**

#### Specifications
**1.** The subsystem SHALL display accurate data collection and analysis on a laptop device.    
**2.** The subsystem SHALL be compatible with wireless data transfer capabilities.  
**3.** The subsystem SHALL wirelessly displays triage signal processing data.   
**4.** The subsystem SHALL wirelessly stream video and audio data.  
**5.** The subsystem SHALL transmit audio to the speaker through either the built-in microphone or an external microphone. 


**These specifications and constraints are rationalized in the Overview of Proposed Solution.**


## Overview of Proposed Solution
The interfacing subsystem is an immediate-time processing and displaying system designed to wirelessly stream audio, video, and telemetry triage signal data maintaining low latency and and high accuracy for crucial medical situations.  

**1. Processing and Displaying Data**

  - A laptop with a minimum of 2 I/O ports to support external connection devices (TP-Link Archer T4U) and charging functions to ensure connectivity and power reliability.
  - A Windows laptop system, having sufficient CPU at 1.5 GHz, <1 GB RAM processing, and H.264/H.265 GPU hardware **[6]** for displaying and decoding/encoding audio streams, video streams, and telemetry data.
  - A laptop system capable of supporting WebRTC and WebSockets through supported browsers (Chrome or Firefox) and supported Python libraries.
  - WebRTC application for direct client-to-client audio and video streaming with low latency on modern browsers. Allowing for successful audio and video transmission for the audio and video devices. **[2]**.
  - Python, HTML, and JavaScript Programming language frameworks offer extensive libraries for decoding and displaying audio, video, and telemetry data and support WebRTC streaming applications.

**2. Data Accuracy and Reliability**

  - The WebRTC application can achieve a <1 ms latency for the audio and video streaming through optimized algorithms and protocols built-in the application **[1]**.
  - WebRTC utilizes Direct Communication, bypassing servers when possible and allowing for client-to-client streaming ensuring transport security and accuracy without adding significant amounts of latency.
  - To optimize data reliability, the implementation of error correction algorithms (FEC and CRC) allows for packet loss recovery and real-time monitoring ensuring correct data transmissions with low-latency communication through WebRTC and WebSocket applications.
  - Memory buffers and streams will be used to ensure that the data will be displayed but not stored in the hard memory of the device and instead discarded after use, ensuring the victims' privacy **[5]**.

## Interface with Other Subsystems
The interfacing subsystem will connect with each subsystem being the main output for all gathered data.
  
The interfacing subsystem must be compatible with the drone communication subsystem to function correctly. This will be completed by attaching a wifi module adaptor (TP-Link Archer T4U Plus **[3]**) to the laptop and drone's USB port acting as a host and client to communicate data to one another. Once a wireless connective bridge is obtained, and created by the drone communication subsystem, the data from each of the signal processing, microphone camera, and vitals sensors subsystems can be outputted to the user with accuracy.   
  
The data will be packaged through necessary Python libraries. Failure at any of these subsystems will result in a lack of accuracy and functionality within the interfacing subsystem.

## Interfacing Block Diagram
![Block Diagram (1)](https://github.com/user-attachments/assets/4bafc49d-c250-4c6c-a0d5-edae34b31c47)

Block Diagram visualizing the different interfaces to each sub module


## Operational Flowchart
![Blank diagram](https://github.com/user-attachments/assets/ecdcaaf4-0390-453f-acaa-63bfb39faf4a)



## BOM

| PART NUMBER            | DESCRIPTION     | Link       |MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:             | :---:    | :---:         | :---:                  |
|840030701535            | [TP-Link Archer T4U Plus]([https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html](https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/)) | https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/| TP-Link | 2 | 19.99| *_Purchased in drone communication subsystem_  |

## Analysis
#### Choosing the Software and Devices
A laptop device with Windows software is a great option for the interfacing subsystem as it supports modern web browsers necessary for WebRTC and WebSocket applications. WebRTC and WebSocket software applications are the perfect choice for the processing and transmission of data for the interfacing subsystem. Both applications have many complementary features, allowing for low latency and synced communication. 

  - WebRTC includes built-in error correction algorithms (FEC and CRC), ensuring that the video and audio stream is correct and accurate.
  - WebRTC's client-to-client base structure will allow for ensured privacy because it eliminates the need for server-based storage. Also benefiting from this structure is the latency times, WebRTC ensures a low-latency time which is necessary for a medical disaster response.
  -  The ease of compatibility and integration with WebRTC and WebSockets are essential for the use of the different applications built using programming languages (Python, JavaScript, and HTML).
  - The latency of <1 second for real-time audio and video streaming has a range at roughly 33-50 feet on a supported 5 GHz band, and roughly 98-131 feet on a supported 2.4 GHz band. The _Archer T4U Plus_ supports, 802.11ac, both 2.4 GHz and 5 GHz bands.
    ##### Mathematical Analysis of latency
    ![IMG_0289](https://github.com/user-attachments/assets/a3eb87ef-6e7c-4c76-ae5e-5fb27532a4ce)
    **_A theoretical analysis of the range at which the latency does not surpass 1 second. A physical test with the hardware implementation and tools will need to be conducted to get the most accurate analysis_**


 

#### Programming Languages
Python, JavaScript, and HTML for the interfacing subsystem are pivotal for the success of the interfacing subsystem. 

  - Python is the perfect choice for data processing and backend. Python offers lots of support for data manipulation which is necessary when dealing with backend telemetry data processing (vital sensor data).
 - Python offers extensive amounts of libraries including _OpenCV_ or _GStreamer_. These are excellent choices for video and audio data processing and transmission and are a compatible application with WebRTC and WebSockets.

  - JavaScript is a dynamic option for real-time data and is compatible with most interactive web applications such as WebRTC and WebSockets. Although Python is a powerful processing language it lacks the real-time interaction that JavaScript offers. Pairing the two together will be optimal in effectively creating complex computation of sensor data handling through Python and communicating the back-end logic in a real-time JavaScript application.
  - HTML is a powerful tool for creating a visualized interface that is accessible across many modern browsers. The integration of HTML is a requirement to display all the processed data.
  - HTML offers lots of pre-built libraries that are great options for WebRTC audio and video streaming as well as live data graphs for real-time vitals data.




## References

**[1]** [WebRTC Latency](https://www.nanocosmos.de/blog/webrtc-latency/)   
**[2]** [WebRTC](https://webrtc.org)   
**[3]** [Drone Communication Subsystem](https://github.com/superhotbacon/F24_Team5_DARPA_Triage_Drone/blob/communication-detailed-design/Reports/Detailed%20Design/drone%20communications%20subsystem.md)  
**[4]** [Conceptual Design](https://github.com/superhotbacon/F24_Team5_DARPA_Triage_Drone/blob/main/Reports/Conceputal%20Design%20Final/Conceptual%20Design.md)  
**[5]** [Data Privacy](https://www.rcrcmagazine.org/2021/01/data-protection-critical-humanitarian-action/)  
**[6]** [GPU Hardware](https://www.pugetsystems.com/labs/articles/what-h-264-and-h-265-hardware-decoding-is-supported-in-premiere-pro-2120/?srsltid=AfmBOoobeUiZLAJkBTojUF9R8mp34t64RI2c3WcPgzpm_UJpcW_yobUm)  
**[7]** [Typical Packet Size](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://mentor.ieee.org/802.11/dcn/00/11-00-0349-00-000e-models-for-mpeg2-and-video-conferencing.ppt%23:~:text%3DTypically%2520for%2520Internet%2520environment%2520packet%2520size%2520can%2520vary%2520from%2520200%252D1500%2520bytes&ved=2ahUKEwjwtN-x_J6KAxWRKUQIHRwiFvYQFnoECA8QAw&usg=AOvVaw30QwI1wXxvZkdeWfSPSb8l)  
**[8]** [TPLink Archer T4U Plus](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html](https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/))

