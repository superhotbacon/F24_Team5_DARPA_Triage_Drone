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
  - The system SHALL do the above within 20 seconds.
  - The system SHALL be able to interface and provide data to a processor.
  - The system SHALL function despite inconsistent target positions.

## Overview of Proposed Solution ---Reference Data Sheets Here---

The Infineon Demo BGT60UTR11AIP radar sensor is the solution that will fulfill all of the previously mentioned constraints and specifications. It is a 60GHz Frequency Modulated Continuous Wave (FMCW) radar; however, it also posseses the capability to operate in a Continuous Wave (CW) mode.  
  
The board is roughly 3 inches by 1 inch and ways less than a gram. The board itself is an Infineon Radar Baseboard MCU7 Plus with a BGT60UTR11AIP radar sensor shiled strapped to it. It can be operated via pins on the board or through a micro-usb connection. Infineon provides an extensive SDK for using this technology as well as a ready-to-go GUI.  

This solution has the range, sensitivity, and programmable capabilities as well as weight limitations ideal for fulfilling the role of this submodel.





[1]https://www.fcc.gov/general/radio-frequency-safety-0
