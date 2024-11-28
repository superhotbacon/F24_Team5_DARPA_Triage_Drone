# Vitals Sensor

Selecting and correctly configuring a radar sensor is a crucial aspect to this project since most of the Triage Method is reliant on the device's ability to gather data on a person's heart and respiratory rate. This detailed design explains the steps taken to identify the ideal sensor and what will be required to operate it going forward. For the sake of coherency, the terms radar sensor and vitals sensor may be used interchangeably as they refer to the same system.

## Function of the Subsystem

The purpose of this subsystem is to be the interface by which the drone, and therefore its users, gathers data from a human it is near. Since the purpose of this project is to build an unmanned device to determine the condition of people in a dangerous environment, it follows that the project team must add some technology to the device that can obtain data that is indicative of human safety and wellbeing. Some of the most commonly used measures to determine this include a heart and respiratory rate, as both of these are imperative for human life.  
  
This subsystem will provide access to that information and transmit it to the Signal Processing Subsystem for further evaluation.

## Constraints
  - The system MUST not push the project budget to exceed $5,000 (target is less than $200).
  - The system MUST not weigh enough to significantly disturb the drone (target is less than 0.5lb or 230g).
  - The system MUST not consume so much power as to debilitate the drone.
  - The system MUST not exceed a Specific Absorption Rate of 1.6 W/kg. [1]

## Specifications
  - The system SHALL accurately detect milimeter-sized motion made by a heart from at least a meter away.
  - The system SHALL accurately detect respiration from at least a meter away.
  - The system SHALL be able to interface and provide data to a processor.
  - The system SHALL function despite inconsistent target positions.

## Overview of Proposed Solution ---Reference Data Sheets Here---

The Infineon Demo BGT60UTR11AIP radar sensor is the solution that will fulfill all of the previously mentioned constraints and specifications. It is a 60GHz Frequency Modulated Continuous Wave (FMCW) radar; however, it also posseses the capability to operate in a Continuous Wave (CW) mode. [2]
  
The board is roughly 3 inches by 1 inch and ways less than a gram. The board itself is an Infineon Radar Baseboard MCU7 Plus with a BGT60UTR11AIP radar sensor shield strapped to it. It can be operated via pins on the board or through a micro-usb connection. Infineon provides an extensive SDK for using this technology as well as a ready-to-go GUI.  

This solution has the range, sensitivity, and programmable capabilities as well as weight limitations ideal for fulfilling the role of this submodel.

## Interface with other Subsystems
The vitals sensor subsystem will solely interface with the signal processing subsystem. This will be done by connecting the micro-usb port of the Infineon board to one of the multiple Jetson Nano USB ports. The data this system provides will be used by other systems, but only after being processed by the Jetson.  

The micro-usb to USB connection works as a serial port. The other pins on the board may or may not be utilized as a form of digital communication if the need arises. If the pins are used, the team can choose to communicate to the board via SPI (pins A9, A11-A14, A17, and D31) or I2C (pins D28 and D27).[3]

## Printed Circuit Board Layout
### The MCU7 Plus
![Screenshot 2024-11-27 at 14-13-56 Radar Baseboard MCU7 Plus - Infineon-UG155750_Radar_Baseboard_MCU7_Plus-UserManual-v01_10-EN pdf](https://github.com/user-attachments/assets/539a4d73-efa8-49ba-b2a5-1d3741bd2c0d) [3]
### The Infineon BGT60UTRA11AIP Shield
![Screenshot 2024-11-27 at 14-15-46 BGT60UTR11AIP shield - Infineon-UG091947_BGT60UTR11AIP_shield-UserManual-v02_00-EN pdf](https://github.com/user-attachments/assets/dbb881b1-d0e5-415a-84e5-36553a94b0ad) [4]
### The Shield on the MCU
![BGT60UBOARD](https://github.com/user-attachments/assets/f1d708ee-65c7-43d5-9d63-6a0106a353eb) [4]

## Conceptual Schematic
![Screenshot 2024-11-27 at 14-24-46 BGT60UTR11AIP - Infineon-BGT60UTR11AIP-DataSheet-v01_00-EN pdf](https://github.com/user-attachments/assets/055f3a14-bc56-4fa8-a496-5f588c475fac)
 [5]

## BOM
Below is this subsystem's BOM. Since the majority of the engineering required for this subsystem is operation and not construction, there are only two required pieces of equipment.

| PART NUMBER            | DESCRIPTION     | MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:    | :---:         | :---:                  |
 DEMOBGT60UTR11AIPTOBO1               | [Infineon Demo BGT60UTR11AIP](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html](https://www.infineon.com/cms/en/product/evaluation-boards/demo-bgt60utr11aip/)) | Infineon | 1 | $177.37 | $177.37|
| 7T9MV4              | [Micro-USB Cable](https://www.digikey.ee/en/products/detail/analog-devices-inc/ADXL203EB/665382](https://www.amazon.com/Amazon-Basics-Charging-Transfer-Gold-Plated/dp/B07232M876/ref=sr_1_1_ffob_sspa?crid=3NYG1TYD80F2E&dib=eyJ2IjoiMSJ9.BTH-JaqRBvQbWEP_82nsg3yEMXYNI64nU1zKdoVJWozaRJLjffc2AxH49bpUSKMxRmhycVZ-cl4f3JYFXJR7O-3Ep6gIb74Q28Zai-27w_6wIuGL0XXqfFrfD50MVW2j8NuEYlM7A9VtHiTLiQdeKxmE8xwIcwvhPZrYZnz8vqIc6Mny7I9Ial4L6WIZNb2fiShtVv-b9LdoFAx3AEaVMsWlQ0dKs3R5FriiQQhb82U.-ba0OBlMVvDP-XYOVvnkis2BssC956V1D6XXpyLtQnw&dib_tag=se&keywords=microusb%2Busb%2Bcable&qid=1732739767&sprefix=microusb%2Caps%2C107&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1)) | Amazon | 1 | $7.59 | $7.59 |

## Analysis
When it comes to obtaining readings on a subject's hear and respiratory rate via radar, there is no sure way method of accomplishing this goal yet. IEEE Xplore has reported at least 2200 papers on this topic [6], and the interest in this challenge has not slowed down. Researching what to use to fulfill the roles of this subsystem was challenging as there are truly many options to choose from. However, the Infineon BGT60UTRA11AIP and the MCU7 Plus are feature rich and are capable of abiding by the previously mentioned constraints and fulfilling the previously mentioned specifications.  

The Infineon radar sensor is inherently a FMCW type radar. Multiple projects have tried to accomplish vital sensing via radar with a CW type radar, but the latter is limited. CW radar can only detect phase differences amidst readings; FMCW can do that as well as detect changes in frequency [7]. Essentially, FMCW proivde users with more data to process during observations, making it more precise.  

The solution is cheap and small enough to fit the constraints. Anything bigger or requiring of some sort of assembly would prove potentially clunky and/or draining to the drone. The other systems will not suffer from the Infineon device's power consumptionn either as it boasts a low power consumption of less than 2W when in use [8].  

The device has a range of 15m, which is more than enough to meet the proposed specification. In additiion, because the radar sensor operates at a frequency of 60GHz, it is considered a mm-Wave radar device since it is capable of detecting changes as small as a few millimeters which is ideal for heart rate detection as a heartbeat causes minimal displacement.  

Lastly, the added MCU7 Plus provides users with the ability to use Infineon's radar SDK. The board itself is capable of some processing that allows for the data to be acquired in different modes (FMCW or CW) as well as to what measure would a user like the data to already be processed. One can obtain completely raw data from the device, but the board and SDK also allows users to receive data in specificly organized objects or classes so further processing is simplified. THis is a huge advantage as it will allow the project to be developed more quickly and flexilby. 
  





[1]https://www.fcc.gov/general/radio-frequency-safety-0  
[2]https://www.infineon.com/cms/en/product/evaluation-boards/demo-bgt60utr11aip/  
[3]https://www.infineon.com/dgdl/Infineon-UG155750_Radar_Baseboard_MCU7_Plus-UserManual-v01_10-EN.pdf?fileId=8ac78c8c88704c7a01888bb70e617c92  
[4]https://www.infineon.com/dgdl/Infineon-UG091947_BGT60UTR11AIP_shield-UserManual-v02_00-EN.pdf?fileId=8ac78c8c88704c7a01888bade09f7c8b  
[5]https://www.infineon.com/dgdl/Infineon-BGT60UTR11AIP-DataSheet-v01_00-EN.pdf?fileId=8ac78c8c88ae21230188d3eb8b9307b3
[6][2025_Radar_Challenge_DynamicHR.pdf](https://github.com/user-attachments/files/17950353/2025_Radar_Challenge_DynamicHR.pdf)
[7]https://pmc.ncbi.nlm.nih.gov/articles/PMC9104941/#B29-sensors-22-03106
[8]https://www.infineon.com/dgdl/FAQ_BGT60_70_80.pdf?fileId=5546d46146d18cb4014700efb33138bc
