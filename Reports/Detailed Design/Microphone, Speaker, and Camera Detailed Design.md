# Microphone, Speaker and Camera Detailed Design

## Function of the subsystem

The function of the Microphone, Speaker, and Camera subsystem is to integrate a microphone, speaker, and two analog cameras onto a drone, all connected to a Jetson Nano. The design includes signal processing on the Jetson Nano to eliminate propeller noise captured by the microphone, ensuring clear audio transmission. Additionally, the speaker and cameras facilitate communication and video streaming. An assembly design will also be required to show how all components will be mounted onto the drone. The Jetson Nano will work with both the microphone filtering subsystem and the signal processing. Therefore, using efficient coding algorithms is imperative to conserve the drone’s battery.

## Specifications  
1. The microphone shall operate within a frequency range of 0.5 Hz to 500 Hz to capture biological signals effectively.  
2. The speaker shall support frequencies from 300 Hz to 3.4 kHz for effective human voice transmission.   
3. The speaker shall produce sufficient output power to enable clear communication at distances up to 10 meters.  
4. The speaker shall provide intelligible audio output despite interference from drone noise.  
5. The camera shall provide a minimum resolution of 1080p for clear and detailed video capture.   
6. The camera shall operate at a minimum of 30 frames per second (fps) to ensure smooth video playback.  
7. The camera shall have a wide field of view sufficient to capture subjects while compensating for drone motion.  
8. The all components shall operate within the power limits of 22v auxiliary power to ensure sustained operation.  

### Constraints  
1. The combined weight of the microphone, speaker, and cameras shall not exceed the payload capacity of the drone of 3.3 lbs.  
2. All components shall operate reliably in outdoor environments, including exposure to wind and moderate temperature fluctuations.  
3. The microphone, speaker, and cameras shall not cause interference with each other or with other electronic components on the drone.


---

### Overview of Proposed Solution
**Microphone:**  
The microphone on the drone captures ambient sounds, including both drone-generated noise and external audio. The audio is sent to the Jetson Nano for filtering and processing, allowing the system to focus on relevant sounds while minimizing unwanted noise from the drone. Due to the simplicity of eliminating propeller noise, a low-pass filter will be implemented to ensure that no frequencies above 200 Hz interfere with the microphone’s output.

**Camera Selection**
Two analog cameras are added for real-time video streaming:
- Camera 1: Front-facing for navigation.
- Camera 2: Downward-facing for inspection and monitoring.  

**Speaker:**    
The speaker on the drone transmits audio from the Jetson Nano, enabling two-way communication. This allows the drone to relay instructions, alerts, or other audio signals to the operator or nearby individuals. TO ensure that the Microphone doenst pick up anything for the speaker. the two parts will only be able to activate inversly or neither.

**Analog Cameras:**  
The drone is equipped with analog cameras that provide real-time video footage. These cameras allow for visual monitoring of the drone’s surroundings, which is essential for navigation, obstacle avoidance, and ensuring safe operation during flight.

**Jetson Nano:**  
The Jetson Nano will control all signal processing through a Python script, communicating with each component in the system. The primary objective is to allow the user to easily toggle between the microphone and speaker via an interface subsystem, ensuring that only one is active at a time. First, the analog microphone signal must be demodulated into a digital signal. Following that, a noise filtering algorithm will be developed. The Python script will define a sampling rate and a cutoff frequency (set at 200 Hz). The sampling rate will be determined through testing to find the optimal balance between battery usage and audio quality. The script will also include the necessary functions and logic to handle real-time input and output between the components, ensuring that audio signals are processed accurately and efficiently, while effectively removing unwanted noise.

**Flow Chart**  
![image](https://github.com/user-attachments/assets/c916fd9a-ba51-471f-9eec-0d0adf3f64d6)
---
### **Schematics**
![image](https://github.com/user-attachments/assets/97daee00-25fe-4d1d-8c16-72a19f47e9d0)

#### **Port Configuration**
- **J13**: Camera 1  
- **J49**: Camera 2  
- **J32**: Microphone 
- **J33-1 & 2**: Speaker 1, Speaker 2

 ### **Port Block Diagram**
 ![image](https://github.com/user-attachments/assets/80233d77-9b1a-4ed1-8fa3-c5fc713f02e6)


---

#### **Bode Plot Diagram**
**Noice Filter:**  
The initial approach to filtering the microphone signal involved designing a notch filter in MATLAB to understand its transfer function. The objective was to isolate and remove unwanted noise at specific frequencies. However, after further evaluation, it was decided to transition to a software-based solution by programming the filter in Python. This shift was motivated by cost-effectiveness, as it required fewer physical components, and provided greater flexibility for real-time signal processing on the Jetson Nano. By implementing the filter in software, the same results could be achieved without additional hardware, making the solution more efficient and manageable for the drone’s system.
![image](https://github.com/user-attachments/assets/bdf308ee-3b87-46b2-972f-0ff9423bfde4)

---
### **Attaching components to the drone**
The Jetson Nano, along with the two cameras, speaker, and microphone, will be mounted on the drone using custom 3D-printed brackets designed for lightweight support. The 3D-printed parts will have low infill to reduce overall weight while maintaining structural integrity. The Jetson Nano will be secured to the drone’s main frame with a rigid 3D-printed base, ensuring stability without adding unnecessary bulk. The two cameras will be attached using adjustable 3D-printed mounts, with Camera 1 positioned at the front for forward vision and Camera 2 placed at an angle to capture an alternative perspective. The microphone will be positioned away from the propellers and motors, using a lightweight arm or enclosure to minimize direct exposure to wind and mechanical noise. The speaker will be mounted at the lower part of the drone to ensure clear audio projection. Wiring will be neatly routed along the frame, secured with cable ties, to prevent loose connections and interference while keeping the system lightweight and efficient.


## **BOM**
| PART NUMBER  | DESCRIPTION      | Link      |MANUFACTURER NAME    | QUANTITY| COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:        | :---:            | :---:     | :---:               | :---:   | :---:         | :---:                  |
| 054114569014 | Camera           | [Amazon: Camera](https://www.amazon.com/SoloGood-Camera-Ratel2-Starlight-1200TVL/dp/B08T74F3WB/ref=pd_ci_mcx_di_int_sccai_cn_d_sccl_3_4/144-9551838-3238701?pd_rd_w=YxQkM&content-id=amzn1.sym.751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_p=751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_r=Q9AJA8MX952BJCT92BHM&pd_rd_wg=BfBvl&pd_rd_r=30b4bc70-a359-4dd8-acab-b23bd076afef&pd_rd_i=B08T74F3WB&th=1)      |   Caddx             |    2    |     32.99     |  65.97                 |
| 641076944258 |Microphone        | [Amazon: Microphone](https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1)      |   PowerDeWise       |    1    |     29.99     |  29.99                 |
| 641076944258 | 4 PCS Speaker 3  | [Amazon: Speaker](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5)      |   HANXI01           |    1    |     9.99      |  9.99                  |


---

### **Analysis**
The subsystem integrating the microphone, speaker, and cameras on the drone, connected to the Jetson Nano, is designed to enable efficient real-time signal processing and communication. The microphone captures both ambient sounds and noise generated by the drone’s propellers. To ensure that only relevant audio signals are processed, the Jetson Nano is used to filter out the propeller noise. A low-pass filter will be implemented to attenuate frequencies above 200 Hz, focusing on biological signals while reducing interference.

The two analog cameras are strategically placed to capture different perspectives. Camera 1 is front-facing for navigation purposes, while Camera 2 is positioned downward for monitoring and inspection. Both cameras will provide real-time video, which is crucial for the drone's autonomous navigation and obstacle avoidance.

The speaker will enable two-way communication, allowing the drone to transmit audio signals. To avoid interference with the microphone, the microphone and speaker will operate inversely—only one component will be active at any given time. This prevents the microphone from picking up sound from the speaker, ensuring clear audio transmission.

The Jetson Nano will be the central control unit for all signal processing. It will handle the demodulation of the microphone’s analog signal, convert it into a digital signal, and apply a noise filtering algorithm to ensure high-quality audio output. A sampling rate and cutoff frequency of 200 Hz will be defined based on testing, optimizing the balance between battery consumption and audio quality. The Python script running on the Jetson Nano will facilitate real-time processing and communication between the components, ensuring efficient and accurate signal transmission.

All components will be securely mounted onto the drone using custom 3D-printed brackets. These parts will feature low infill to minimize weight while maintaining structural integrity, ensuring the drone remains stable during flight. The careful placement and secure attachment of the components will help prevent interference between the microphone, speaker, and cameras, contributing to overall system performance.


### **References**

[1].https://electricala2z.com/electrical-circuits/low-pass-and-high-pass-filter-frequency-response/

[2].https://courses.grainger.illinois.edu/ece401/fa2021/lectures/lec25.pdf

[3].https://www.electrical4u.com/band-stop-notch-filter/

[4].https://developer.nvidia.com/embedded/learn/jetson-nano-2gb-devkit-user-guide

[5].https://www.electronics-tutorials.ws/filter/band-stop-filter.html

