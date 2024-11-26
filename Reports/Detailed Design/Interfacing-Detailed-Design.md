## General Requirements for the Document

The document should include:

- Synopsis of the suggested solution
- Interfaces among different subsystems
- A buildable diagram*
- An operational flowchart*
- A comprehensive Bill of Materials (BOM)
- Analysis of crucial design decisions
- Execution plan considering skill sets and time requirements


## Introduction
This document delineates a fully comprehensive system design for the interfacing subsystem. Focusing on the integration within the broader solution, the specifications and constraints relevant to the interfacing, and the process and justification of each crucial design step that constructs the solution. 


## Interfacing Subsystem Function

The interfacing subsystem will function as the project's wireless data visualization via the use of any compatible laptop device. This involves gathering and receiving the processed data wirelessly from the Jetson Nano computing device attached to the drone and displaying live, engaging data visuals for the user within near-immediate transmission and processing times. Live video and audio taken from a camera and microphone connected to the drone will be streamed to the laptop, along with displaying data from the triage signal processing systems wirelessly. 

## Specifications and Constraints

#### Constraints

**1.** The subsystem SHALL maintain an error rate of less than 1% to ensure accurate transmitted data display.  
  
\- This 1% error rate is necessary to complete accurate triage to not compromise the reliability of the system in crucial situations. 

**2.** The subsystem SHALL clock latency of <1 second for video, audio, and data streaming.  
  
\- A <1 second clock latency ensures immediate responsive video and audio streaming which is deemed necessary during a time of crisis. A high latency can cause disruptive connectivity and sync between the audio and video. 

**3.** The subsystem SHALL process and display data without storing any received data.  

\- Abiding by the Code of Medical Ethics this requirement ensures the victims' privacy during a time of medical crisis [].

#### Specifications

**1.** The subsystem SHALL display data collection and analysis on a laptop device.   
**2.** The subsystem SHALL be compatible with wireless data transfer capabilities.  
**3.** The subsystem SHALL wirelessly displays triage signal processing data.  
**4.** The subsystem SHALL wirelessly stream video and audio data.  


## Overview of Proposed Solution


## Interface with Other Subsystems

Provide detailed information about the inputs, outputs, and data transferred to other subsystems. Ensure specificity and thoroughness, clarifying the method of communication and the nature of the data transmitted.


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

https://www.nanocosmos.de/blog/webrtc-latency/
