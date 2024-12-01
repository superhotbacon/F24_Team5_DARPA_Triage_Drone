# Microphone, Speaker and Camera Detailed Design

## Function of the subsystem

The function of this subsystem is to design a system for a drone equipped with a microphone, speaker, and two analog cameras, all connected with a Jetson Nano. The design includes a **notch filter** to eliminate propeller noise captured by the microphone, ensuring clear audio transmission, while the speaker and cameras facilitate communication and video streaming.

## Specifications and Constraints  
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
- **Microphone:**  
  The microphone on the drone captures ambient sounds, including drone-generated noise and external audio. The audio is sent to the Jetson Nano for filtering and processing, enabling the system to focus on relevant sounds while minimizing unwanted noise from the drone.

- **Speaker:**  
  The speaker on the drone transmits audio from the Jetson Nano, enabling two-way communication. This allows the drone to relay instructions, alerts, or other audio signals to the operator or nearby individuals.

- **Analog Cameras:**  
  The drone is equipped with analog cameras that provide real-time video footage. These cameras allow for visual monitoring of the drone’s surroundings, which is essential for navigation, obstacle avoidance, and ensuring safe operation during flight.


---
### **Block Diagram**
The system is structured as follows:
[4]![image](https://github.com/user-attachments/assets/52ff63d4-1bc3-4037-bdfe-920a455aa097)

---

### **Noise Filtering Using a Notch Filter**

#### **Drone Propeller Noise**
Drone propellers typically generate a fundamental noise frequency around 200–400 Hz[2], with harmonics at multiples of this frequency. This noise interferes with microphone recordings.

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
| PART NUMBER            | DESCRIPTION     | Link       |MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:             | :---:    | :---:         | :---:                  |
| 054114569014          | SoloGood Caddx FPV Micro Camera Ratel2 Starlight 1200TVL 1/1.8'' 2.1mm NTSC PAL 16:9 4:3 Switchable Super WDR for FPV Racing | [https://www.amazon.com/wireless-USB-WiFi-Adapter-PC/dp/B08KHV7H1S/](https://www.amazon.com/SoloGood-Camera-Ratel2-Starlight-1200TVL/dp/B08T74F3WB/ref=pd_ci_mcx_di_int_sccai_cn_d_sccl_3_4/144-9551838-3238701?pd_rd_w=YxQkM&content-id=amzn1.sym.751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_p=751acc83-5c05-42d0-a15e-303622651e1e&pf_rd_r=Q9AJA8MX952BJCT92BHM&pd_rd_wg=BfBvl&pd_rd_r=30b4bc70-a359-4dd8-acab-b23bd076afef&pd_rd_i=B08T74F3WB&th=1)| Caddx | 2 | 32.99| 65.97  |
| 641076944258                       |PowerDeWise Professional Grade Lavalier Clip On Microphone - Lav Mic for Camera Phone iPhone GoPro Video Recording ASMR - Small Noise Cancelling 3.5mm Tiny Shirt Microphone with Easy Clip On System                  | https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1           |   PowerDeWise           |    1    |       29.99           |     29.99         |
| 641076944258                       |4 PCS Speaker 3 Watt 8 Ohm Mini Speaker 8ohm 3w Loundspeaker Micro Speaker for Arduino with JST-PH2.0 Interface for Small Electronic Projects Advertising Machines LCD TV Monitors                 | [https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5?crid=1VGRHCYJDM6DB&dib=eyJ2IjoiMSJ9.SQqKoCQYYmAuVxmwueAXo923OT1_KZn4a1ANHotecQd-AVLfXBX1m4ZPCUh3w9kq28PyZF_AZAKCDjVicy3L2o2gH94rBUIEG5HZ91t0K72O1HBgnR0pnn6DQML8bHcd5EkpGu3IxWYCd5AItFBSNR2yQpl3EOjJz2pTqtYmYqk17goNE1f28ysmEB1a0TAOgdNu3GSpq9pRpkr0SZiNNzPJWbm9VA6qL_h2SU0MfQw.zhZOjVB2EDSLraEsnZa53UDEeq7tzuD5Oh_7lNEG3N8&dib_tag=se&keywords=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit&qid=1732855344&sprefix=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit%2Caps%2C117&sr=8-5&th=1)           |   HANXI01           |    1    |       9.99           |     9.99         |
| TLC2201CP                       |OP AMP                | [[https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5?crid=1VGRHCYJDM6DB&dib=eyJ2IjoiMSJ9.SQqKoCQYYmAuVxmwueAXo923OT1_KZn4a1ANHotecQd-AVLfXBX1m4ZPCUh3w9kq28PyZF_AZAKCDjVicy3L2o2gH94rBUIEG5HZ91t0K72O1HBgnR0pnn6DQML8bHcd5EkpGu3IxWYCd5AItFBSNR2yQpl3EOjJz2pTqtYmYqk17goNE1f28ysmEB1a0TAOgdNu3GSpq9pRpkr0SZiNNzPJWbm9VA6qL_h2SU0MfQw.zhZOjVB2EDSLraEsnZa53UDEeq7tzuD5Oh_7lNEG3N8&dib_tag=se&keywords=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit&qid=1732855344&sprefix=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit%2Caps%2C117&sr=8-5&th=1)](https://www.newark.com/texas-instruments/tlc2201cp/op-amp-cmos-low-noise-2201-dip8/dp/54AH1570?CMP=KNC-BUSA-GEN-Shopping-ALL&mckv=s_dc|pcrid||plid||kword||match|e|slid||product|54AH1570|pgrid|1231453304461926|ptaid|pla-4580565455222458:aud-806258620|&msclkid=a092432a3e6d15370efc246374f13359)           |   TEXAS INSTRUMENTS           |    3    |       7.22           |     21.66        |
|      7362                | 10k Resistor            | [[[https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5?crid=1VGRHCYJDM6DB&dib=eyJ2IjoiMSJ9.SQqKoCQYYmAuVxmwueAXo923OT1_KZn4a1ANHotecQd-AVLfXBX1m4ZPCUh3w9kq28PyZF_AZAKCDjVicy3L2o2gH94rBUIEG5HZ91t0K72O1HBgnR0pnn6DQML8bHcd5EkpGu3IxWYCd5AItFBSNR2yQpl3EOjJz2pTqtYmYqk17goNE1f28ysmEB1a0TAOgdNu3GSpq9pRpkr0SZiNNzPJWbm9VA6qL_h2SU0MfQw.zhZOjVB2EDSLraEsnZa53UDEeq7tzuD5Oh_7lNEG3N8&dib_tag=se&keywords=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit&qid=1732855344&sprefix=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit%2Caps%2C117&sr=8-5&th=1)](https://www.newark.com/texas-instruments/tlc2201cp/op-amp-cmos-low-noise-2201-dip8/dp/54AH1570?CMP=KNC-BUSA-GEN-Shopping-ALL&mckv=s_dc|pcrid||plid||kword||match|e|slid||product|54AH1570|pgrid|1231453304461926|ptaid|pla-4580565455222458:aud-806258620|&msclkid=a092432a3e6d15370efc246374f13359)](https://www.stewmac.com/electronics/pedals/pedal-components-and-parts/resistors/?msclkid=d1da933342b317655e70f47a09f3e22e&utm_source=bing&utm_medium=cpc&utm_campaign=CP%20%7C%20MF%20%7C%20BNG%20%7C%20SHOP%20%7C%20NBR%20%7C%20All%20Products&utm_term=4576373583312051&utm_content=All%20Products)           |   STEWMAC           |    5    |       1.08           |     5.40       |
|    7357                  | 1k Resistor            | [[[https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5?crid=1VGRHCYJDM6DB&dib=eyJ2IjoiMSJ9.SQqKoCQYYmAuVxmwueAXo923OT1_KZn4a1ANHotecQd-AVLfXBX1m4ZPCUh3w9kq28PyZF_AZAKCDjVicy3L2o2gH94rBUIEG5HZ91t0K72O1HBgnR0pnn6DQML8bHcd5EkpGu3IxWYCd5AItFBSNR2yQpl3EOjJz2pTqtYmYqk17goNE1f28ysmEB1a0TAOgdNu3GSpq9pRpkr0SZiNNzPJWbm9VA6qL_h2SU0MfQw.zhZOjVB2EDSLraEsnZa53UDEeq7tzuD5Oh_7lNEG3N8&dib_tag=se&keywords=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit&qid=1732855344&sprefix=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit%2Caps%2C117&sr=8-5&th=1)](https://www.newark.com/texas-instruments/tlc2201cp/op-amp-cmos-low-noise-2201-dip8/dp/54AH1570?CMP=KNC-BUSA-GEN-Shopping-ALL&mckv=s_dc|pcrid||plid||kword||match|e|slid||product|54AH1570|pgrid|1231453304461926|ptaid|pla-4580565455222458:aud-806258620|&msclkid=a092432a3e6d15370efc246374f13359)](https://www.stewmac.com/electronics/pedals/pedal-components-and-parts/resistors/?msclkid=d1da933342b317655e70f47a09f3e22e&utm_source=bing&utm_medium=cpc&utm_campaign=CP%20%7C%20MF%20%7C%20BNG%20%7C%20SHOP%20%7C%20NBR%20%7C%20All%20Products&utm_term=4576373583312051&utm_content=All%20Products)           |   STEWMAC           |    5    |       1.08           |     5.40       |
|    7377                  | 3k Resistor            | [[[https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5?crid=1VGRHCYJDM6DB&dib=eyJ2IjoiMSJ9.SQqKoCQYYmAuVxmwueAXo923OT1_KZn4a1ANHotecQd-AVLfXBX1m4ZPCUh3w9kq28PyZF_AZAKCDjVicy3L2o2gH94rBUIEG5HZ91t0K72O1HBgnR0pnn6DQML8bHcd5EkpGu3IxWYCd5AItFBSNR2yQpl3EOjJz2pTqtYmYqk17goNE1f28ysmEB1a0TAOgdNu3GSpq9pRpkr0SZiNNzPJWbm9VA6qL_h2SU0MfQw.zhZOjVB2EDSLraEsnZa53UDEeq7tzuD5Oh_7lNEG3N8&dib_tag=se&keywords=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit&qid=1732855344&sprefix=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit%2Caps%2C117&sr=8-5&th=1)](https://www.newark.com/texas-instruments/tlc2201cp/op-amp-cmos-low-noise-2201-dip8/dp/54AH1570?CMP=KNC-BUSA-GEN-Shopping-ALL&mckv=s_dc|pcrid||plid||kword||match|e|slid||product|54AH1570|pgrid|1231453304461926|ptaid|pla-4580565455222458:aud-806258620|&msclkid=a092432a3e6d15370efc246374f13359)](https://www.stewmac.com/electronics/pedals/pedal-components-and-parts/resistors/?msclkid=d1da933342b317655e70f47a09f3e22e&utm_source=bing&utm_medium=cpc&utm_campaign=CP%20%7C%20MF%20%7C%20BNG%20%7C%20SHOP%20%7C%20NBR%20%7C%20All%20Products&utm_term=4576373583312051&utm_content=All%20Products)           |   STEWMAC           |    5    |       1.08           |     5.40       |
|    7314                  | 1u Capcitor          | [[[https://www.amazon.com/Professional-Microphone-Omnidirectional-Recording-Conference/dp/B01AG56HYQ/ref=rvi_d_sccl_14/144-9551838-3238701?pd_rd_w=Aq1sP&content-id=amzn1.sym.f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_p=f5690a4d-f2bb-45d9-9d1b-736fee412437&pf_rd_r=WN2H7TGAXJ3HR815ETNS&pd_rd_wg=PsTil&pd_rd_r=df48aa10-57fd-4c64-a194-51e172731714&pd_rd_i=B01AG56HYQ&psc=1](https://www.amazon.com/Loundspeaker-JST-PH2-0-Interface-Electronic-Advertising/dp/B0B4D1BN4F/ref=sr_1_5?crid=1VGRHCYJDM6DB&dib=eyJ2IjoiMSJ9.SQqKoCQYYmAuVxmwueAXo923OT1_KZn4a1ANHotecQd-AVLfXBX1m4ZPCUh3w9kq28PyZF_AZAKCDjVicy3L2o2gH94rBUIEG5HZ91t0K72O1HBgnR0pnn6DQML8bHcd5EkpGu3IxWYCd5AItFBSNR2yQpl3EOjJz2pTqtYmYqk17goNE1f28ysmEB1a0TAOgdNu3GSpq9pRpkr0SZiNNzPJWbm9VA6qL_h2SU0MfQw.zhZOjVB2EDSLraEsnZa53UDEeq7tzuD5Oh_7lNEG3N8&dib_tag=se&keywords=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit&qid=1732855344&sprefix=amazon%2Bsmall%2Bspeakers%2Bfor%2Bcircuit%2Caps%2C117&sr=8-5&th=1)](https://www.newark.com/texas-instruments/tlc2201cp/op-amp-cmos-low-noise-2201-dip8/dp/54AH1570?CMP=KNC-BUSA-GEN-Shopping-ALL&mckv=s_dc|pcrid||plid||kword||match|e|slid||product|54AH1570|pgrid|1231453304461926|ptaid|pla-4580565455222458:aud-806258620|&msclkid=a092432a3e6d15370efc246374f13359)](https://www.stewmac.com/electronics/pedals/pedal-components-and-parts/resistors/?msclkid=d1da933342b317655e70f47a09f3e22e&utm_source=bing&utm_medium=cpc&utm_campaign=CP%20%7C%20MF%20%7C%20BNG%20%7C%20SHOP%20%7C%20NBR%20%7C%20All%20Products&utm_term=4576373583312051&utm_content=All%20Products)           |   STEWMAC           |    5    |       0.7           |     0.35      |


---

### **Challenges and Mitigation**
While the notch filter addresses specific noise frequencies, additional low-pass or high-pass filters may be necessary for broader noise rejection. These supplementary filters can help eliminate any residual interference that the notch filter cannot handle. However, until I can test the drone’s noise characteristics during operation, it is difficult to fully identify and filter out all unwanted frequencies. During the drone's assembly phase, I plan to conduct tests to measure the actual noise generated. This will allow me to fine-tune the filters to target the specific noise profile more effectively. noise rejection.

---

### **Conclusion**
This design provides a robust system for real-time audio-video communication while eliminating drone noise. The Jetson Nano’s processing capabilities enable seamless integration and efficient operation, making it suitable for drone applications requiring high performance and precision.

### **References**

[1].https://electricala2z.com/electrical-circuits/low-pass-and-high-pass-filter-frequency-response/

[2].https://courses.grainger.illinois.edu/ece401/fa2021/lectures/lec25.pdf

[3].https://www.electrical4u.com/band-stop-notch-filter/

[4].Conceptual Design

[5].https://www.electronics-tutorials.ws/filter/band-stop-filter.html

