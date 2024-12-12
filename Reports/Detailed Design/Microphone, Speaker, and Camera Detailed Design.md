# Microphone, Speaker and Camera Detailed Design

## Function of the subsystem

The function of this subsystem is to design a system for a drone equipped with a microphone, speaker, and two analog cameras, all connected with a Jetson Nano. The design includes a **notch filter** to eliminate propeller noise captured by the microphone, ensuring clear audio transmission, while the speaker and cameras facilitate communication and video streaming.

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
The microphone on the drone captures ambient sounds, including drone-generated noise and external audio. The audio is sent to the Jetson Nano for filtering and processing, enabling the system to focus on relevant sounds while minimizing unwanted noise from the drone.

**Speaker:**  
The speaker on the drone transmits audio from the Jetson Nano, enabling two-way communication. This allows the drone to relay instructions, alerts, or other audio signals to the operator or nearby individuals.

**Analog Cameras:**  
The drone is equipped with analog cameras that provide real-time video footage. These cameras allow for visual monitoring of the drone’s surroundings, which is essential for navigation, obstacle avoidance, and ensuring safe operation during flight.


---
### **Schematics**
The Jetson Nano layout:
[4]![image](![image](https://github.com/user-attachments/assets/97daee00-25fe-4d1d-8c16-72a19f47e9d0)

#### **Port Configuration**
- **J13**: Camera 1  
- **J49**: Camera 2  
- **J32**: Microphone and Notch Filter 
- **J33-1 & 2**: Speaker 1, Speaker 2

 ### **Port Block Diagram**
 ![image](https://github.com/user-attachments/assets/80233d77-9b1a-4ed1-8fa3-c5fc713f02e6)


---

### **Noise Filtering Using a Notch Filter**

#### **Drone Propeller Noise**
Drone propellers typically generate a fundamental noise frequency around 200–400 Hz[2], with harmonics at multiples of this frequency. This noise interferes with microphone recordings.

#### **Notch Filter Design**
![image](https://github.com/user-attachments/assets/6a24eb77-4823-4df0-841e-c012aa48de6b)


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
The microphone signal passes through the notch filter before reaching the Jetson Nano’s audio input. The filtered signal removes the drone noise while retaining useful audio.

---

### **Speaker for Communication**

The speaker enables two-way communication between the drone and a victim:
- **Signal Flow**:
  Audio from the ground control is processed by the Jetson Nano. The Jetson Nano’s DAC (Digital-to-Analog Converter) outputs the audio signal. The signal is amplified and sent to the drone’s speaker.
- **Amplification Circuit**:
  A small Class-D audio amplifier is used to drive the speaker efficiently. A low-pass filter at the amplifier input ensures smooth signal reproduction.


---

### **Analog Cameras for Video Streaming**

#### **Camera Selection**
Two analog cameras are added for real-time video streaming:
- **Camera 1:** Front-facing for navigation.
- **Camera 2:** Downward-facing for inspection and monitoring.

#### **Signal Conversion**
Analog cameras output composite video signals (e.g., NTSC or PAL). These signals must be digitized for the Jetson Nano. Each camera connects to an analog-to-digital converter (e.g., USB video capture adapters). The digitized video is fed into the Jetson Nano via USB.


## **BOM**
| PART NUMBER  | DESCRIPTION      | Link      |MANUFACTURER NAME    | QUANTITY| COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:        | :---:            | :---:     | :---:               | :---:   | :---:         | :---:                  |
| 054114569014 | Camera           | [Amazon: Camera](https://www.amazon.com/SoloGood-Camera-Ratel2-Starlight-1200TVL/dp/B08T74F3WB/ref=pd_ci_mcx_di_int_sccai_cn_d_sccl_3_4/144-9551838-3238701?pd_rd_w=YxQkM&content-id=amzn1.sym.751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_p=751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_r=Q9AJA8MX952BJCT92BHM&pd_rd_wg=BfBvl&pd_rd_r=30b4bc70-a359-4dd8-acab-b23bd076afef&pd_rd_i=B08T74F3WB&th=1)      |   Caddx             |    2    |     32.99     |  65.97                 |
| 641076944258 |Microphone        | [Amazon: Microphone](https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1)      |   PowerDeWise       |    1    |     29.99     |  29.99                 |
| 641076944258 | 4 PCS Speaker 3  | [Amazon: Speaker](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5)      |   HANXI01           |    1    |     9.99      |  9.99                  |
| B07WQWPLSP       | OP AMP LM358     | [Amazon: OP AMP](https://www.amazon.com/BOJACK-LM358P-Operational-Amplifier-LM358N/dp/B07WQWPLSP/ref=sr_1_1_sspa?crid=1JMR29377YQWP&dib=eyJ2IjoiMSJ9.LSp_oRxWDe1toRPBDAn23V3iZ7ry76AwtqZ5tQ62HjX8-aGfMtXTLrw_F8nfj3A4GvHgXQDa5uCWx1d6OPUl_w4vh8rRxY4kE5DVs5v8oaILAN-gneWTkgxYiHK2e_VOk706fxN3QeCt4s1E7_3PFxFmFJND8KAC6cli0vG2mOOczmT6pxIpFNDYJEipdBdEYuQlz4t2V-PSknkB1u5qjeEhB_6oS-7sQwHyCdWO7tM.tX9RBvNIrq4wt-SO1kFa2g8IN-6zwlQROtZMUo21EDI&dib_tag=se&keywords=lm358+op+amp&qid=1733452269&sprefix=LM358%2Caps%2C187&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)      |   BOJACK  |    1    |     6.99      |  6.99                 |
|   B072BL2VX1 | 10k, 1k, 3k Resistor     | [Amazon: Pack of Resisters](https://www.amazon.com/Elegoo-Values-Resistor-Assortment-Compliant/dp/B072BL2VX1/ref=sr_1_11?adgrpid=1334807683268756&dib=eyJ2IjoiMSJ9.6LwS_eL7GUDzrQTHCbHoUrXbUU6GcLf0Oh8KSANGZZcKLQV9E25Etr_y-yw_ibsxsUMQKiaoy3v_NUdjJBJBd16oxGNYWNBu1omlyGmU6lJdlYDy_EAuuHzvzGLdBONOJJlHLmBO5f9wS9NKR7eXevuXdIzZGzBtkLbsQsK-SbKwonpXQ_b-4WhgfoP14ZgF2wh3hsFTeQRplu5Fy1y5_y_uAX4tEInTBPESEXO5Fx0.ZmMxoRQ3nHuHH2YXgTIRbEiO8F4hE1dWvl3iFtlsMc4&dib_tag=se&hvadid=83425629443795&hvbmt=bp&hvdev=c&hvlocphy=84181&hvnetw=o&hvqmt=p&hvtargid=kwd-83425831793952%3Aloc-190&hydadcr=24663_13493294&keywords=10k+resistor&qid=1733452455&sr=8-11)      |   ELEGOO            |    1    |     9.99      |  9.99                  |
|    B0CMQC587X   | 1u Capcitor      | [1u Capcitor](https://www.amazon.com/ALLECIN-Electrolytic-Capacitor-0-2x0-43in-Capacitors/dp/B0CMQC587X/ref=sr_1_1_sspa?crid=3QZTZ36DZN51S&dib=eyJ2IjoiMSJ9.hsAm4pqGQ38GqvW3cA8gw_Vy691_Ovizo0e_MeOfj11e7Tf9oaFEtQ24qpl9aL3UpsgLkayB-dbQsgqRnGrivJVFQgB3zMzzx8aKbp20rUkOyhHYEu0Aygqb2_nWGRTsYWctMexbeO6Ga5a3S_MCFiH__em-GDdlSi5Yp1mz4QVvSUkoAsUTnAfpzpHInY3tJNYct-c6_Pm75OwEEsNWdphEOcNX1_uIyfeMrDmux7s.LQrTrPYdLJ0AUdGAZJ6qA7vHMlhZPZjwqv2ijBfft6I&dib_tag=se&keywords=1u%2Bcapacitor&qid=1733453195&sprefix=1u%2Bcapacitor%2Caps%2C139&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1)      |   ALLECIN           |    1    |     5.99       |  5.99                  |
|    B09QMNV6J1   | PCB Board    | [PCB Board](https://www.amazon.com/SchmalzTech-Electronic-Circuit-Prototype-ST-PERF-1-1/dp/B09QMNV6J1/ref=sr_1_9?crid=1B9ZBSO7MFE08&dib=eyJ2IjoiMSJ9.Zu_9MlJdzbeq8tv531drZjpTDlcmfjniMEkyCko4374U3tqhmQmhzEO8s8qM9OmQc62cfXgdgF0VwWrVu3_xe0BD-MAqf4EgoTJrxokwY-Kk1nacOFx1_tUMYUFkbyRfksTVOzmJbwo-t-GkMTpky0Fqt9u1K2-ZpbBD8dIRgK4JzqGuwHWSYgZtP4A8tKqWhZnpfxL0TiebCocZSxhKRhjj3NyTUxiyxhvsaUNRAZE.A_4CWiiiztRpMRoPWQ1zoE9OBHox0kCzaczKJxdOiz0&dib_tag=se&keywords=small%2Bpcb%2Bboard&qid=1733457234&sprefix=small%2Bpcb%2Bboard%2Caps%2C123&sr=8-9&th=1)      |   SchmalzTech, LLC      |    2    |     5.99       |  11.98                  |


---

### **Challenges and Mitigation**
While the notch filter addresses specific noise frequencies, additional low-pass or high-pass filters may be necessary for broader noise rejection. These supplementary filters can help eliminate any residual interference that the notch filter cannot handle. However, until I can test the drone’s noise characteristics during operation, it is difficult to fully identify and filter out all unwanted frequencies. During the drone's assembly phase, I plan to conduct tests to measure the actual noise generated. This will allow me to fine-tune the filters to target the specific noise profile more effectively. noise rejection.

---

### **Analysis**
The microphone will be securely mounted on the drone in a position that allows it to effectively capture relevant sounds, particularly the biological signals, while minimizing interference from the drone's propeller noise. The output from the microphone will be connected to the input of the notch filter circuit, which will require proper soldering to ensure stable signal transmission. The notch filter itself will be assembled on a printed circuit board (PCB) where the components such as resistors, capacitors, and operational amplifiers will be placed and soldered according to the design layout. This is critical for ensuring the filter works as intended, attenuating noise in the 200–400 Hz range, which corresponds to the drone's propeller frequencies, while allowing other audio frequencies to pass through without distortion. Once the circuit is assembled, it will be tested to ensure the correct frequency response is achieved, using tools like an oscilloscope to verify that the noise has been effectively filtered.

After the notch filter has been assembled and tested, the output will be routed to the Jetson Nano for further processing. The Jetson Nano will receive the cleaned audio signal from the filter and process it for communication or data analysis. This connection will require careful wiring to ensure stable signal transmission and prevent any potential interference.

The speaker, which will be responsible for transmitting audio from the Jetson Nano, will be connected to the system’s output. The Jetson Nano will process and output the audio signal, which will then be sent to the speaker, ensuring clear two-way communication. The speaker will be mounted in a location on the drone that maximizes its ability to transmit audio clearly, without interference from other components.

All components when assembled will be needing to all be attached together with the drone and the Jetson nano. The Current Drone allows for multiple connections and attachments so will be very easy to attach components. It will need to be kept in mind that all component's weights need to be evenly distributed and centered so that the drone can be stable.

Once all components are assembled and connected, the system will undergo comprehensive testing. This will include verifying that the microphone captures audio without interference from the drone’s motors, ensuring the cameras provide clear, smooth video, and confirming that the Jetson Nano processes both audio and video signals effectively. The entire system will be powered by the drone’s 22V auxiliary power source, and voltage regulators will be used where necessary to ensure each component receives the correct voltage. Additionally, the wiring must be carefully managed to prevent signal interference, and insulation should be applied to prevent short circuits. After the assembly and testing phase, the subsystem will be ready for integration into the drone, ensuring all components work together seamlessly while maintaining the drone’s power and weight constraints.

### **References**

[1].https://electricala2z.com/electrical-circuits/low-pass-and-high-pass-filter-frequency-response/

[2].https://courses.grainger.illinois.edu/ece401/fa2021/lectures/lec25.pdf

[3].https://www.electrical4u.com/band-stop-notch-filter/

[4].https://developer.nvidia.com/embedded/learn/jetson-nano-2gb-devkit-user-guide

[5].https://www.electronics-tutorials.ws/filter/band-stop-filter.html

