# Interfacing Detailed Design
This document delineates a fully comprehensive system design for the interfacing subsystem. Focusing on the integration within the broader solution, the specifications and constraints relevant to the interfacing, and the process and justification of each crucial design step that constructs the solution. 


## Interfacing Subsystem Function

The interfacing subsystem will function as the project's wireless data visualization via the use of a compatible laptop device. This involves wirelessly gathering and receiving the processed data from the Jetson Nano computing device attached to the drone and displaying live, engaging data visuals for the user within near-immediate transmission and processing times. Live video and audio from the camera and microphone connected to the drone will be streamed to the laptop, and data from the triage signal processing systems will be displayed wirelessly. 

## Specifications and Constraints

#### Constraints

**1.** The subsystem MUST maintain an error rate of less than 1% to ensure accurate transmitted data display.  
**2.** The subsystem MUST clock a latency of <1 second for video, audio, and data streaming.  
**3.** The subsystem MUST process and display data without storing any of the received data.  

#### Specifications
**1.** The subsystem SHALL display accurate data collection and analysis on a laptop device.    
**2.** The subsystem SHALL be compatible with wireless data transfer capabilities.  
**3.** The subsystem SHALL wirelessly displays triage signal processing data.   
**4.** The subsystem SHALL wirelessly stream video and audio data.  

**These specifications and constraints are rationalized in the Overview of Proposed Solution.**


## Overview of Proposed Solution
The interfacing subsystem is an immediate-time processing and displaying system designed to wirelessly stream audio, video, and telemetry triage signal data maintaining low latency and and high accuracy for crucial medical situations.  

**1. Processing and Displaying Data**

  - A laptop with a minimum of 2 I/O ports to support external connection devices (TP-Link Archer T4U) and charging functions to ensure connectivity and power reliability.
  - A Windows or macOS laptop system, having sufficient CPU at 1.5 GHz, <1 GB RAM processing, and H.264/H.265 GPU hardware for displaying and decoding/encoding audio streams, video streams, and telemetry data.
  - A laptop system capable of supporting WebRTC and WebSockets through supported browsers (Chrome or Firefox) and supported Python libraries.
  - WebRTC application for direct client-to-client audio and video streaming with low latency on modern browsers [2].
  - Python, HTML, and JavaScript Programming language frameworks offer extensive libraries for decoding and displaying audio, video, and telemetry data and support WebRTC streaming applications. 

**2. Data Accuracy and Reliability**

  - The WebRTC application can achieve a <1 ms latency for the audio and video streaming through optimized algorithms and protocols built-in the application.
  - WebRTC utilizes Direct Communication, bypassing servers when possible and allowing for client-to-client streaming ensuring transport security and accuracy without adding significant amounts of latency.
  - To optimize data reliability, the implementation of error correction algorithms (FEC and CRC) allows for packet loss recovery and real-time monitoring ensuring correct data transmissions with low-latency communication through WebRTC and WebSocket applications.
  - Memory buffers and streams will be used to ensure that the data will be displayed but not stored in the hard memory of the device and instead discarded after use, ensuring the victims' privacy [].

## Interface with Other Subsystems
The interfacing subsystem will connect with each subsystem being the main output for all gathered data. The interfacing subsystem must be compatible with the drone communication subsystem to function correctly. This will be completed by attaching a wifi module adaptor (TP-Link Archer T4U Plus [3]) to the laptop and drone's USB port acting as a host and client to communicate data to one another. Once a wireless connective bridge is obtained, and created by the drone communication subsystem, the data from each of the signal processing, microphone camera, and vitals sensors subsystems can be outputted to the user with accuracy. The data will be packaged through necessary Python libraries. Failure at any of these subsystems will result in a lack of accuracy and functionality within the interfacing subsystem.


## 3D Model of Custom Mechanical Components

Should there be mechanical elements, display diverse views of the necessary 3D models within the document. Ensure the image's readability and appropriate scaling. Offer explanations as required.

## Operational Flowchart

For sections including a software component, produce a chart that demonstrates the decision-making process of the microcontroller. It should provide an overview of the device's function without exhaustive detail.


## BOM

A complete list of all components needed for the design must be given with the cost of each component and the total cost of the subsystem. The BOM should be a markdown table. Make sure to to provide the manufacteror, part number, distributor, distributor part number, quantity, and price. Also provide a url where the product can be purchased from. If the componenet is refernced on your schematic make sure to include the component name.

Provide a comprehensive list of all necessary components along with their prices and the total cost of the subsystem. This information should be presented in a tabular format, complete with the manufacturer, part number, distributor, distributor part number, quantity, price, and purchasing website URL. If the component is included in your schematic diagram, ensure inclusion of the component name on the BOM (i.e R1, C45, U4).

## Analysis

Deliver a full and relevant analysis of the design demonstrating that it should meet the constraints and accomplish the intended function. This analysis should be comprehensive and well articulated for persuasiveness.

## References

All sources that have contributed to the detailed design and are not considered common knowledge should be duly cited, incorporating multiple references.

**[1]** https://www.nanocosmos.de/blog/webrtc-latency/  
**[2]** https://webrtc.org  
**[3]** [Drone Communication Subsystem] (https://github.com/superhotbacon/F24_Team5_DARPA_Triage_Drone/blob/communication-detailed-design/Reports/Detailed%20Design/drone%20communications%20subsystem.md)



## General Requirements for the Document

The document should include:

- Synopsis of the suggested solution
- Interfaces among different subsystems
- A buildable diagram*
- An operational flowchart*
- A comprehensive Bill of Materials (BOM)
- Analysis of crucial design decisions
- Execution plan considering skill sets and time requirements
