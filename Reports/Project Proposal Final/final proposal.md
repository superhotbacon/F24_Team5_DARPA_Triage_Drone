## **Introduction**
&nbsp; Aviation drones have become useful tools for scanning areas that are too difficult or too dangerous for first responders to reach. Taking a step further, aviation drones can assist in assessing the severity of an emergency situation. During a situation such as this, having a drone with sensors and AI capabilities can assess the medical conditions of the victims, allowing first responders to prioritize the most affected areas. This would grant first responders the ability to use resources such as time and aid more efficiently, ultimately resulting in more lives saved. Currently, there are no aviation drones that have the capability to categorize victims of an emergency by prioritizing critical injuries. Due to this problem, the Defense Advanced Research Projects Agency (DARPA) has come up with a challenge to provide first responders with this technology. 

\-The drone with integrated cameras, sensors, and AI algorithms shall fly above the ground to quickly detect possible cassualties in large areas. 

\-The drone shall fly close to victims and use sensors to collect medical data about the injured person. 

&nbsp; In rescue missions, our drone could provide initial canvasing of an area to pinpoint locations of possible human casualties as well as assess a victims critical condition. This could be followed up via helicocpter or ground medical team by way of utmost effeciency. This proposal will set out to outline a project that will build a drone to suit these objectives. In the coming sections, the specific goals and objectives will be laid out as well as specifications and constraints that our team will strive to overcome. Our team will also examine current solutions to this problem and other approaches and argue why our project is more effective.

## **CHALLENGES/OBSTACLES**

&nbsp; -Harsh environments: The drone will need to remain steady and controlled in weather conditions that might make that difficult. 

&nbsp; -Weight: After adding the necessary sensor and camera components a larger drone might be imperative. 

&nbsp; -Flight Duration: Drones typically have a short flight duartion, especially one with the size and weigth needed for this functionality. 

&nbsp; -Range: The distance a drone can travel is dependent on weather, battery size, and weight. 

&nbsp; In addition to autonomous capabilities, the drone will be able to be manually controlled. This will provide more functionality to the drone. As we add equipment to the drone, it becomes heavier so our team will need to take care to get the lightest equipment possible while also reigning in our budget. Care will also have to be taken in order to safely charge the drone. Over charging Lithium Polymer batteries can be very dangerous. This is especially of concern as Li-Po batteries are a popular choice for drones.

## **SPECIFICATION**

**1. System shall obtain the presence of a heartbeat and its frequency. (range 0.45 to 2.92Hz).**  
&nbsp; \-Measure of success: Able to detect a simulated heartbeat accurately of a stationary target 70% of the time. 

**2. System shall accomplish all functionality from at least one meter away.**  
&nbsp; \-Measure of success:  Drone completes all the listed measures of success from 1 meter away.

**3. System shall obtain the breathing rate and frequency (range 0.13 to 1 Hz).**  
&nbsp; \-Measure of success: Using group members breathing at a set rate at room temperature as a control, the drone accurately reads this set rate within 20% margin of error.

**4. System shall give vocal commands using speaker and listen for response to evaluate the cognitive ability of a victim.**  
&nbsp; \-Measure of success: Being able to verbally communicate from operator to drone. The operator and victim should be able to clearly hear each other.

**5. System shall limit the audio frequency received between 80 to 255 Hz.**  
&nbsp; \-Measure of success: Test different frequencies in and out of range to ensure the drone receives only specified frequencies.

**6. System shall not store any voice recordings in compliance with the two party consent laws for select states.**  
&nbsp; \-Measure of success: Provide documentation that software does not save audio recordings in non dynamic memory.

**7. System shall operate at full functionality for 15 to 60 minutes.**  
&nbsp; \-Measure of success: Time the drone in each operating condition until the drone runs out of battery. Drone will inform the user when the battery is below 10%.

**8. System shall display triage results and vitals wirelessly.**  
&nbsp; \-Measure of success: Triage results will display accurate data on controllers interface that is readable for first responders.

**9. System shall weigh less than 20 pounds as per DARPA’s requirements for the Drone Triage Challenge or DTC [1].**  
&nbsp; \-Measure of success: The drone will be placed on a scale and will read under 20 lbs.

**10. System shall display results in close to real time**  
&nbsp; \-Measure of success: Using synced stop watches, two group members will be placed at max range away. The drone will then take simulated measurements and the results will be analyzed to find the average latency for measurements.

**Constaints**

\- The drone SHALL be user friendly.  
\- The drone SHALL have a integrated system for security.  
\- The drone SHALL remain under 400 ft above ground level **[4]**.  
\- The drone SHALL not exceed 100 mph **[4]**.  
\- The drone SHALL be equipped with anti-collision lighting **[4]**.  

# Relevant Literature

We will have to do some research into the following fields of study to build a successful search and rescue (SAR) drone:
- Vitals detecting via radar
- Image processing
- Drone programming

### Radar
The National Library of Medicine has already done research into reading a subject's vitals at a distance. From their research, it's clear that we'll need to consider the following as we engineer our product:
- How to fine tune our signal to avoid noise generated by the drone or any other external movement.
- How to differentiate between a heart rate and a breathing rate.
- How to consume minimal power with acceptable performance.

### Image Processing
NVIDIA has an article on using the chip our drone will be working with, a jetson nano, for search and rescue purposes. From the text, several steps in the image computing process include:
- Prioritizing speed over detail when observing the landscape.
- Cropping images with likely targets to optimize processing.
- Using an algorithm to train the data.

### Drone Programming
Since our drone will spend the majority of its time searching, it's important to consider portential strategies for navigating any potential terrain. The IEEE explains some important considerations regarding this:
- SAR drones are built to be safe and reliable, following UN regulations.
- SAR drones should avoid disrupting the flow of traffic or any other service.
- SAR drones can optimize their routes to better their performance.

[1]
“Autonomous Vehicles for Emergency Response and Disaster Relief - IEEE Public Safety Technology Initiative,” Ieee.org, 2024. https://publicsafety.ieee.org/topics/autonomous-vehicles-for-emergency-response-and-disaster-relief

‌[2]
“Deep Learning in Aerial Systems Using Jetson | NVIDIA Technical Blog,” NVIDIA Technical Blog, Nov. 03, 2016. https://developer.nvidia.com/blog/deep-learning-in-aerial-systems-jetson/ (accessed Oct. 01, 2024).

[3]
M. Kebe, R. Gadhafi, B. Mohammad, M. Sanduleanu, H. Saleh, and M. Al-Qutayri, “Human Vital Signs Detection Methods and Potential Using Radars: A Review,” Sensors, vol. 20, no. 5, p. 1454, Mar. 2020, doi: https://doi.org/10.3390/s20051454.

###**RESOURCES**


| SUBSYSTEM                          | PART NUMBER            | DESCRIPTION     | MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                              | :---:                  | :---:           | :---:            | :---:    | :---:         | :---:         |
| _Wireless Communication Subsystem_ | 4735-RAKDAP1-0-WB-N-ND | [RAKDAP1-0-WB-N](https://www.digikey.com/en/products/detail/rakwireless-technology-limited/RAKDAP1-0-WB-N/18682780?s=N4IgTCBcDaIEoEEDSARBAFAjCAugXyA) | RAKwireless Technology Limited | 2 | $10.90 | $21.80 |
|                                    | EB0047418              | [RAK811 LPWAN Breakout](https://www.elecbee.com/blog/en-24682-Node-811-Open-Source-Development-Board-with-Built-in-SX1276-Low-Power-Consumption-and-Long-Distance-Transceiver) | RAKwireless Technology Limited | 2 | $32.39 | $64.78 |
| _Heartbeat/Respiratory Subsystem_  | 513-NJR4262J           | [24 GHz Doppler Sensor Module](https://www.mouser.com/ProductDetail/Nisshinbo/NJR4262J?qs=d9U39LAeJF3Q43gbNnrW1w%3D%3D) | JRC | 1 | $28.87 | $28.87 |
|                                    | B08S7HYGJM             | [High Precision AD HAT Board Waveshare ADC Module](https://www.amazon.com/Waveshare-High-Precision-Raspberry-ADS1263-Compatible/dp/B08S7HYGJM?th=1) | Waveshare | 1 | $49.99 | $49.99 |
|                                    | OP07CSZ-REEL7TR-ND     | [Prescision Amplifier](https://www.digikey.com/en/products/detail/analog-devices-inc/OP07CSZ-REEL7/995520?utm_adgroup=Analog%20Devices&utm_source=google&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_Focus%20Suppliers&utm_term&utm_content=Analog%20Devices&gclid=Cj0KCQjw6cKiBhD5ARIsAKXUdyYBkOYL-1aWh53aOll8AXXF1uU5lS3YKelAGR3BP4-yuHW5urheIyoaAt-TEALw_wcB) | Texas Instruments | 2 | $2.21 | $4.42| 
|                                    | CF14JT1K00TR-ND        | [1k Ohm 5% 1/4W axial resistor](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT1K00/1830350?utm_adgroup=General&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Zombie%20SKUs&utm_term&utm_content=General&gclid=Cj0KCQjw6cKiBhD5ARIsAKXUdyYzUyry_5jJzcHVz5VKJjgaU44iZpaTrko4jueSd3Ms6wtAu-FjUNYaAqxcEALw_wcB)     | Stackpole Electronics | 2 | $0.10 | $0.20 |
|                                    | CF14JT3K00TR-ND        | [3k Ohm 5% 1/4W axial resistor](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT3K00/1741418) | Stackpole Electronics | 2 | $0.10 | $0.20 |
|                                    | CF14JT15K0TR-ND        | [15k Ohm 5% 1/4W axial resistor](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT15K0/1741298) | Stackpole Electronics | 2 | $0.10 | $0.20 |
|                                    | 338-2641-ND            | [Mica 56 pF 5% 500V Radial](https://www.digikey.com/en/products/detail/cornell-dubilier-electronics-cde/CD15ED560JO3F/1917754) | Cornell Dubilier Electronics (CDE) | 2 | $1.79 | $3.58 |
|                                    | 338-3057-ND            | [Mica 8200 pF 5% 500V Radial](https://www.digikey.com/en/products/detail/cornell-dubilier-electronics-cde/CD30FD822JO3F/1918194) | Cornell Dubilier Electronics (CDE) | 2 | $13.47 | $26.94 |
|                                    | 2191-80.00000358-ND    | [IPS-937 24GHZ RADAR MODULE](https://www.digikey.com/en/products/detail/innosent-gmbh/80-00000358/10416543) | InnoSenT GmbH | 1 | $135.99 | $135.99 |
| _Computing_                        | J1020 V2               | [Jetson Nano Developer Kit](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html) | Nvidia | 1 | $279.00 | $279.00 |
|                                    | RAS-4-4G               | [Raspberry Pi 4 Model B](https://www.amazon.com/Raspberry-Model-2019-Quad-Bluetooth/dp/B07TC2BK1X?th=1) | Raspberry Pi | 1 | $60.98 | $60.98 |
| _Voice Detection Subsystem_        | BOB-19389              | [OPA344, SPH8878LR5H-1 MEMS Omnidirectional Microphones Audio Evaluation Boar](https://www.digikey.com/en/products/detail/sparkfun-electronics/BOB19389/16342333) | SparkFun Electronics | 1 | $6.95 | $6.95 |
|                                    | COM-18343              | [4 Ohms General Purpose Speaker 4 W Top Rectangular](https://www.sparkfun.com/products/18343) | SparkFun Electronics | 1 | $10.95 | $10.95 |
| _Power Subsystem_                  | 3017                   | [DC-DC 5A Buck Converter](https://www.icstation.com/step-down-buck-converter-power-supply-module-125v-adjustable-voltmeter-p-3017.html) | Valefod | 1 | $4.89 | $4.89 |
|                                    | DD39AJPA               | [Positive And Negative Dual Output Power Supply Module](https://www.aliexpress.us/item/3256804028860260.html?src=google&aff_fcid=4f4e2b29191e40388e6ac755398bc5ec-1694653440148-04081-UneMJZVf&aff_fsk=UneMJZVf&aff_platform=aaf&sk=UneMJZVf&aff_trace_key=4f4e2b29191e40388e6ac755398bc5ec-1694653440148-04081-UneMJZVf&terminal_id=d06cb1cdc06c4998b4935111d106946f&afSmartRedirect=y&gatewayAdapt=glo2usa) | eletechsup | 1 | $0.99 | $0.99 |
|                                    | B091TRMFYT             | [NP-F Battery Adapter Plate](https://www.amazon.com/dp/B091TRMFYT?ascsubtag=amzn1.ideas.2WYYMHDV0VVNZ&linkCode=sl1&tag=jetsonhacks-20&linkId=3a4257f3f9f547ba799ddbcec22977d9&language=en_US&ref_=as_li_ss_tl) | SmallRig | 1 | $26.99 | $26.99 |
|                                    | B0BTHSDF4S             | [20 Pcs DC Power Cable 5A 12v DC](https://www.amazon.com/dp/B0BTHSDF4S/ref%3Dsspa_dk_detail_3?psc=1&pd_rd_i=B0BTHSDF4S&pd_rd_w=1OS6v&content-id=amzn1.sym.08ba9b95-1385-44b0-b652-c46acdff309c&pf_rd_p=08ba9b95-1385-44b0-b652-c46acdff309c&pf_rd_r=B74W16YJ43CMEFKHPWKW&pd_rd_wg=M4xV8&pd_rd_r=78ab97fe-0ffb-402f-b35f-0bdd04872f7e&s=industrial&sp_csd=d2lkZ2V0TmFtZT1zcF9kZXRhaWxfdGhlbWF0aWM&customerReviews) | CENTROPOWER | 1 | $9.29 | $9.29 |
|                                    | B078NRLSKL             | [NP-F550 Battery 2-Pack and Wall Charger](https://www.amazon.com/dp/B078NRLSKL/ref%3Dsspa_dk_detail_0?psc=1&pd_rd_i=B078NRLSKL&pd_rd_w=rglsi&content-id=amzn1.sym.08ba9b95-1385-44b0-b652-c46acdff309c&pf_rd_p=08ba9b95-1385-44b0-b652-c46acdff309c&pf_rd_r=WKYPTFJDH5F1FP8918S5&pd_rd_wg=r98KB&pd_rd_r=a3acff40-bd0e-4712-b060-39a785e03d4e&s=electronics&sp_csd=d2lkZ2V0TmFtZT1zcF9kZXRhaWxfdGhlbWF0aWM&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyUUxSNzZQMjBLUlpWJmVuY3J5cHRlZElkPUEwNjM4OTE0MlczWFNPVlNaSEc3MyZlbmNyeXB0ZWRBZElkPUEwNjkyNzg5RzJJWVJMWlJIRTZDJndpZGdldE5hbWU9c3BfZGV0YWlsX3RoZW1hdGljJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ%3D%3D) | Artman | 1 | $26.99 | $26.99 |
| _Drone System_                     | PF728331               | [Parrot ANAFI Ai 4G Robotic Drone](https://www.adorama.com/parpf728331.html#main-product-tabs) | Parrot ANAFI Ai 4G Robotic Drone | 1 | $4,500.00 | $4,500.00 |
|                                    |                        |                                                                                                |                                  |   | **Total Expenses** | $5264.00 |
|                                    |                        |                                                                                                |                                  |   | **Total Quantity** | 29 |


‌
‌
  


