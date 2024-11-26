# Detailed Design

This document delineates the objectives of a comprehensive system design. Upon reviewing this design, the reader should have a clear understanding of:

- How the specific subsystem integrates within the broader solution
- The constraints and specifications relevant to the subsystem
- The rationale behind each crucial design decision
- The procedure for constructing the solution


## General Requirements for the Document

The document should include:

- Explanation of the subsystem’s integration within the overall solution
- Detailed specifications and constraints specific to the subsystem
- Synopsis of the suggested solution
- Interfaces among different subsystems
- 3D models of customized mechanical elements*
- A buildable diagram*
- A Printed Circuit Board (PCB) design layout*
- An operational flowchart*
- A comprehensive Bill of Materials (BOM)
- Analysis of crucial design decisions
- Execution plan considering skill sets and time requirements
*Note: These technical documentation elements are mandatory only when relevant to the particular subsystem.


## Function of the Subsystem
  
  The wireless communication subsystem is responsible for transmitting video and telemetry data from the onboard jetson nano to the PC ground station.
  This will be done over wi-fi communication using two TP-link archer T4U Plus adapters for both the jetson nano and the PC. 

  **Integration with Broader Solution** 
  1. Video Data Transmission:
     - This data will be captured via a camera module and processed with the jetson nano.
     - The video data will be transmitted to the ground station PC using User Datagram Protocol (UDP) sockets for low latancy streaming.
  2. Telemetry Data Transmission:
     - integrated circuits will gather vital signals and send data to the jetson nano to be processed.
     - The telemetry data will be transmitted to the ground station PC using Transmission Control Protocol (TCP) sockets for reliable delivery.
  3. PC Ground Station:
     -Displays video and vitals in real time using software. 

Wi-Fi communication was chosen over 4G communication due to the need for purchasing a data plan for both 4G modules (one for the PC and one for the Jetson Nano). This decision limits the range at which the triage drone can be effective. However for the purpose of the scope outlined by the customer, implementation of wi-fi dongles will provide enough range to be effective.  


## Specifications and Constraints

-  The subsystem shall support a data transfer rate of at least 50 Mbps to handle real time data. [1]
-  The subsystem shall have reliable connectivity at a distance of at least 80 meters using the 2.4GHz band.
-  The jetson nano shall use the TP_Link archer T4U Plus to connect to the host wifi network.
-  The communication subsystem shall be 802.11ac Wi-Fi standards. [1]
-  The communication subsystem shall operate effectivily on a moderately weatherd day as portrayed in the scope.
  

This section should provide a list of constraints applicable to the subsystem, along with the rationale behind these limitations. For instance, constraints can stem from physics-based limitations or requirements, subsystem prerequisites, standards, ethical considerations, or socio-economic factors.

The team should set specifications for each subsystem. These specifications may require modifications, which must be authorized by the team. It could be necessary to impose additional constraints as further information becomes available.

Every subsystem must incorporate at least one constraint stemming from standards, ethics, or socio-economic factors.


## Overview of Proposed Solution
**1. Use the PC as Wi-Fi hotspot host**
- The PC acts as a wi-fi hotspot creating a local wireless network that the Jetson Nano can connect to as a client.
- Using windows enable hotspot through Network and Internet settings -> Mobile Hotspot -> Enable the hotspot (set a unique SSID and password) -> Configure the adapter to share through TP-Link
  
**2. Connect the Jetson Nano as Client**
  - Once the hotspot is active, the Jetson Nano's wi-fi adapter (another TP-Link) is used to connect to it. The Jetson Nano operates as a client on the network, transmitting data to the PC.
  - Use command *nmcli* to connect to the PC's hotspot: nmcli device wifi connect <SSID_NAME> password <PASSWORD>
  - verify the connection using *ifconfig*

**3. Protocols for video transmission**
- On the Jetson Nano use python library *socket* to send video frames.
- Convert the video frames to a compressed format (JPEG, H.264) using libraries such as *OpenCV* or *GStreamer* 
- Send video frames over UDP
- On the PC, recieve the video frames via UDP and display them using *OpenCV* or *GStreamer*

**4. Protocols for telemetry transmission**
- On the Jetson Nano use python library *socket* to send telemetry data.
- Set up TCP client to send telemetry data (strings containing heart rate)
- On the PC set up TCP server to reviece the telemetry data and display it



The communication subsystem establishes a wireless link between the PC (host) and the Jetson Nano (client) for real-time data transfer. It uses TP-Link Archer T4U Plus adapters configured for 802.11ac Wi-Fi communication, leveraging their dual-band capabilities for optimal performance. This ensures low latency and robust data transmission in potentially challenging environments.

Describe the solution and how it will fulfill the specifications and constraints of this subsystem.


## Interface with Other Subsystems
Each of the TP-Link Archer T4U Plus wifi adapters interface via USB connection. One adapter will connect to the Jetson Nano via USB and the other will connect to the ground station PC via USB. 


## 3D Model of Custom Mechanical Components

Should there be mechanical elements, display diverse views of the necessary 3D models within the document. Ensure the image's readability and appropriate scaling. Offer explanations as required.




## Operational Flowchart

For sections including a software component, produce a chart that demonstrates the decision-making process of the microcontroller. It should provide an overview of the device's function without exhaustive detail.


## BOM

A complete list of all components needed for the design must be given with the cost of each component and the total cost of the subsystem. The BOM should be a markdown table. Make sure to to provide the manufacteror, part number, distributor, distributor part number, quantity, and price. Also provide a url where the product can be purchased from. If the componenet is refernced on your schematic make sure to include the component name.

Provide a comprehensive list of all necessary components along with their prices and the total cost of the subsystem. This information should be presented in a tabular format, complete with the manufacturer, part number, distributor, distributor part number, quantity, price, and purchasing website URL. If the component is included in your schematic diagram, ensure inclusion of the component name on the BOM (i.e R1, C45, U4).

## Analysis
**Why choose TP-Link Archer T4U Plus?**
- Dual Band support (2.4GHz band and 5GHz band) allows for flexibility for various enviornments
- High gain antennas imporve range and stability


**Why use the PC as the host?** 
- Easier to have hot spot set up on a stationary device 
- Centralized control over Wi-Fi settings
- Offloads the Jetson Nano's resources for data processing

**Why use TCP for telemetry and UDP for video?** 
- TCP ensure reliable delivery of telemetry data, where packet loss could lead to incorrect readings.
- UDP minimizes latency for video streaming even if some packets are lost. 

Deliver a full and relevant analysis of the design demonstrating that it should meet the constraints and accomplish the intended function. This analysis should be comprehensive and well articulated for persuasiveness.

## References

All sources that have contributed to the detailed design and are not considered common knowledge should be duly cited, incorporating multiple references.
