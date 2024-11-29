# Microphone, Speaker and Camera Detailed Design

## Function of the subsystem

The function of this subsystem is to design a system for a drone equipped with a microphone, speaker, and two analog cameras, all connected with a Jetson Nano. The design includes a **notch filter** to eliminate propeller noise captured by the microphone, ensuring clear audio transmission, while the speaker and cameras facilitate communication and video streaming.

---

### **1. System Overview**
- **Microphone:** Captures sound, including drone noise and external audio sources.
- **Speaker:** Transmits audio signals from the Jetson Nano for two-way communication.
- **Analog Cameras:** Provide real-time video streams for monitoring and control.
- **Jetson Nano:** Serves as the central processing unit, integrating all components for data processing, filtering, and communication.

---

### **2. Noise Filtering Using a Notch Filter**

#### **Drone Propeller Noise**
Drone propellers typically generate a fundamental noise frequency around 200–400 Hz (depending on RPM and blade count), with harmonics at multiples of this frequency. This noise interferes with microphone recordings.

#### **Notch Filter Design**
![image](https://github.com/user-attachments/assets/65323d5d-bf4e-4ce7-a721-03fd42ecb4f6)


As shown above, the notch filter in the circuit effectively combines a high-pass filter and a low-pass filter. The low-pass filter has a cutoff frequency at 200 Hz, while the high-pass filter cuts off frequencies above 400 Hz. These frequency ranges are chosen to replicate the noise characteristics of a drone propeller during flight, as they correspond to the typical vibration frequencies caused by the rotating blades.

In this design, the R Load in the circuit represents the connection to the Jetson Nano, which will process the filtered signals. The Jetson Nano will be used to analyze and interpret the noise-free audio from the microphone on the drone, helping to improve communication or data collection while filtering out unwanted drone motor vibrations.

This filter design is crucial for noise reduction and will allow for clearer audio processing, ensuring that the audio signal received by the Jetson Nano is free from interference caused by the drone’s propeller motor.

#### **Transfer Function**
![image](https://github.com/user-attachments/assets/858fbe2f-f3f5-4c84-b170-81328ad0ce18)


#### **Bode Plot Diagram**
![image](https://github.com/user-attachments/assets/bdf308ee-3b87-46b2-972f-0ff9423bfde4)



#### **Component Selection**

- PCB Board
- 2x1k Resister
- 2x3k Resister
- 3x10k Resister
- 2x1u Resister
- 3 opamps


#### **Integration**
- The microphone signal passes through the notch filter before reaching the Jetson Nano’s audio input.
- The filtered signal removes the drone noise while retaining useful audio.

---

### **3. Speaker for Communication**

The speaker enables two-way communication between the drone and a victim:
- **Signal Flow**:
  - Audio from the ground control is processed by the Jetson Nano.
  - The Jetson Nano’s DAC (Digital-to-Analog Converter) outputs the audio signal.
  - The signal is amplified and sent to the drone’s speaker.
- **Amplification Circuit**:
  - A small Class-D audio amplifier is used to drive the speaker efficiently.
  - A low-pass filter at the amplifier input ensures smooth signal reproduction.
- **Component**:


---

### **4. Analog Cameras for Video Streaming**

#### **Camera Selection**
Two analog cameras are added for real-time video streaming:
- **Camera 1:** Front-facing for navigation.
- **Camera 2:** Downward-facing for inspection and monitoring.

#### **Signal Conversion**
Analog cameras output composite video signals (e.g., NTSC or PAL). These signals must be digitized for the Jetson Nano:
- **Video Capture Module**: Each camera connects to an analog-to-digital converter (e.g., USB video capture adapters).
- The digitized video is fed into the Jetson Nano via USB.

#### **Camera Integration**
- The Jetson Nano processes video streams in parallel using its GPU.
- The Nano supports video encoding and streaming through software like **GStreamer** for efficient transmission.

#### **Camera Component**

---

### **6. Block Diagram**
The system is structured as follows:

## BOM
| PART NUMBER            | DESCRIPTION     | Link       |MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:             | :---:    | :---:         | :---:                  |
| 054114569014          | SoloGood Caddx FPV Micro Camera Ratel2 Starlight 1200TVL 1/1.8'' 2.1mm NTSC PAL 16:9 4:3 Switchable Super WDR for FPV Racing | [https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/](https://www.amazon.com/SoloGood-Camera-Ratel2-Starlight-1200TVL/dp/B08T74F3WB/ref=pd_ci_mcx_di_int_sccai_cn_d_sccl_3_4/144-9551838-3238701?pd_rd_w=YxQkM&content-id=amzn1.sym.751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_p=751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_r=Q9AJA8MX952BJCT92BHM&pd_rd_wg=BfBvl&pd_rd_r=30b4bc70-a359-4dd8-acab-b23bd076afef&pd_rd_i=B08T74F3WB&th=1)| Caddx | 2 | 32.99| 65.97  |
| 641076944258                       |PowerDeWise Professional Grade Lavalier Clip On Microphone - Lav Mic for Camera Phone iPhone GoPro Video Recording ASMR - Small Noise Cancelling 3.5mm Tiny Shirt Microphone with Easy Clip On System                  | https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1           |   PowerDeWise           |    1    |       29.99           |     29.99         |


---

### **7. Challenges and Mitigation**
- **Noise Interference**:
  - While the notch filter addresses specific noise frequencies, additional low-pass or high-pass filters may be necessary for broader noise rejection. These supplementary filters can help eliminate any residual interference that the notch filter cannot handle. However, until I can test the drone’s noise characteristics during operation, it is difficult to fully identify and filter out all unwanted frequencies. During the drone's assembly phase, I plan to conduct tests to measure the actual noise generated. This will allow me to fine-tune the filters to target the specific noise profile more effectively. noise rejection.
---

### **8. Conclusion**
This design provides a robust system for real-time audio-video communication while eliminating drone noise. The Jetson Nano’s processing capabilities enable seamless integration and efficient operation, making it suitable for drone applications requiring high performance and precision.
