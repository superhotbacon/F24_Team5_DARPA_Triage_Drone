# Vitals Sensor

Selecting and correctly configuring a radar sensor is a crucial aspect to this project since most of the Triage Method is reliant on the device's ability to gather data on a person's heart and respiratory rate. This detailed design explains the steps taken to identify the ideal sensor and what will be required to operate it going forward. For the sake of coherency, the terms radar sensor and vitals sensor may be used interchangeably as they refer to the same system.

## Function of the Subsystem

The purpose of this subsystem is to be the interface by which the drone, and therefore its users, gathers data from a human it is near. Since the purpose of this project is to build an unmanned device to determine the condition of people in a dangerous environment, it follows that the project team must add some technology to the device that can obtain data that is indicative of human safety and wellbeing. Some of the most commonly used measures to determine this include a heart and respiratory rate, as both of these are imperative for human life.  
  
This subsystem will provide access to that information and transmit it to the Signal Processing Subsystem for further evaluation.
