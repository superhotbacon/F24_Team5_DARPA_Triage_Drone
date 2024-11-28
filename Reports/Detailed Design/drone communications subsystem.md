## Drone Communication Subsystem


**Function of the Subsystem**
  
  The wireless communication subsystem is responsible for transmitting video and telemetry data from the onboard Jetson Nano to the PC ground station.
  This will be done over wi-fi communication using two TP-link archer T4U Plus adapters for both the Jetson Nano and the PC. The TP-Link archer T4U plus wi-fi adapters are dual band devices that are designed to enhance wireless connectivity. They support high speed internet with speeds up to 1300 Mbps on the 2.4GHz band and 867 Mbps on the 5GHz band. They are equipped with high gain adjustable antennas for increased range and signal stability. Each device is compatible with a PC running windows and the Jetson Nano via USB. 

  **Integration with Broader Solution** 
  1. Video Data Transmission:
     - This data will be captured via a camera module and processed with the jetson nano.
     - The video data will be transmitted to the ground station PC using User Datagram Protocol (UDP) sockets for low latancy streaming.
  2. Telemetry Data Transmission:
     - integrated circuits will gather vital signals and send data to the jetson nano to be processed.
     - The telemetry data will be transmitted to the ground station PC using Transmission Control Protocol (TCP) sockets for reliable delivery.
  3. PC Ground Station:
     - Displays video and vitals in real time using software.
        


## Specifications 
**The subsystem shall operate using IEEE 802.11ac wi-fi for video and telemetry data transfer** [5].
- The IEEE 802.11ac standard supports high data rates and dual-band operation, enabling efficient and low-latency communication. This standard is suitable for real-time video streaming and telemetry data transmission within the operating range.


**The PC ground station shall serve as the Wi-Fi hotspot for establishing the network connection**
- Configuring the PC as the host simplifies setup, centralizes control, and provides a stable Wi-Fi network. This offloads resource-intensive networking tasks from the Jetson Nano.

**The Jetson Nano shall transmit video data using UDP to minimize latency** [6]. 
  - UDP is a connectionless protocol optimized for speed, which is essential for real-time video transmission where occasional packet loss is acceptable.

**The Jetson Nano shall transmit telemetry data using TCP to ensure reliable delivery**
- TCP's reliable connection protocol allows for reliable data delivery which is crucial for accurate data transfer.

## Constraints
**The subsystem must operate within the range limitations of the 802.11ac standard, typically up to 100 meters in open spaces** [2]. 
- Wi-Fi signal strength and range are affected by obstacles, interference, and the chosen frequency band. 100 meters should be enough range to operate effectively as defined in the scope of the emergency situation.

**The TP-Link adapters must be compatible with the Jetson Nano’s operating system and drivers**
- Each wi-fi adapter can plug into the respected device via a USB connection.

  **The subsystem must operate within the power constraints of the Jetson Nano and PC USB ports** [7]. 
  - USB 3.0 connections allow the device to draw 4.5 Watts of power. The adapters must not draw this much power at maximum operation.  
     


## Overview of Proposed Solution

The communication subsystem establishes a wireless link between the PC (host) and the Jetson Nano (client) for real-time data transfer. It uses TP-Link Archer T4U Plus adapters configured for 802.11ac Wi-Fi communication, leveraging their dual-band capabilities for optimal performance. This ensures low latency and robust data transmission in potentially challenging environments.


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




## Interface with Other Subsystems
Each of the TP-Link Archer T4U Plus wifi adapters interface via USB connection. One adapter will connect to the Jetson Nano via USB and the other will connect to the ground station PC via USB. 




## Operational Flowcharts
![Drawing 2](https://hackmd.io/_uploads/SJZTQ8rXke.png)





## BOM
| PART NUMBER            | DESCRIPTION     | Link       |MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:             | :---:    | :---:         | :---:                  |
|840030701535            | [TP-Link Archer T4U Plus]([https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html](https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/)) | https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/| TP-Link | 2 | 19.99| 40.00  |





## Analysis
When choosing the method of communication between the drone and the ground control device, there are a few options to consider.

**1. RF Modules** 
- RF modules would be a great option if the drone only needed to transmit telemetry data such as the heart and respiratory rate of the target. However, RF modules have limited bandwith that support low data rates. This is not an ideal solution for wirelessly transmitting video [3].

**2. 4G modules** 
- Another option to wirelessly transmit data from onboard the drone is provide the Jetson Nano and the PC cellular capabilities by using two 4G modules that can connect with the Jetson Nano and the PC. This is a great option, however one would need to provide a cellular data plan for each device. The problem arises when figuring out who would fit the bill for each of these data plans. This is not a viable soultion for the purposes of this project [4].

**3. Wi-Fi Dongles** 
-One can provide wi-fi capabilities to the Jetson Nano and the PC without internet connection by using two wi-fi module adapters that plug into each device. Doing this allows the Jetson Nano to connect to the PC hotspot via host/client wifi connection. The draw back to this method is it would limit the range of connectablility between the Jetson and the ground station PC. However, using two TP-Link archer T4U pluses allows for enough range and bandwidth to wirelessly transmit video and telemetry data from the onboard Jetson Nano downt to the ground station PC. This method is the best suited for demonstrating the effectiveness of the triage drone [1].  


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
[1]. https://www.tp-link.com/us/home-networking/usb-adapter/archer-t4u-plus/#specifications

[2]. Conceptual Design

[3]. https://www.electro-tech-online.com/threads/rf-modules-which-can-handle-high-number-of-bytes-per-second.163528/

[4]. https://www.pusr.com/news/4g-lte-modem-functions-and-applications.html

[5]. https://www.cisco.com/c/en/us/products/wireless/what-is-802-11ac.html

[6]. https://www.cloudflare.com/learning/ddos/glossary/user-datagram-protocol-udp/

[7]. https://tripplite.eaton.com/products/usb-charging#:~:text=USB%203.0%20and%203.1%20allow,these%20%22default%22%20power%20levels.&text=*%20In%202021%2C%20USB%2DIF,Extended%20Power%20Range%20(EPR).

