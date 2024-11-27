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


Where:


#### **Component Selection**

- Example for 200 Hz:


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



---

### **7. Challenges and Mitigation**
- **Noise Interference**:
  - Additional low-pass or high-pass filters can complement the notch filter for broader noise rejection.
- **Latency**:
  - Optimized data processing pipelines using the Jetson Nano’s GPU ensure low-latency operation.
---

### **8. Conclusion**
This design provides a robust system for real-time audio-video communication while eliminating drone noise. The Jetson Nano’s processing capabilities enable seamless integration and efficient operation, making it suitable for drone applications requiring high performance and precision.
