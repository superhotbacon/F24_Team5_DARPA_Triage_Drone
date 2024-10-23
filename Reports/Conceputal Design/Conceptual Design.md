## Introduction

The following conceptual design wll lay out the general solution to the DARPA triage drone challenge [1].

## Introducing the problem


The porblem proposed is to create a system that will manually fly to individuals in an emergency situation and read vital signs in terms of heart rate, respiratory rate, and cognition. Then the system must relay that information back to the user and rank the victim in terms of the START triage method. 
To understand the scope of the problem, the customer has outlined a specific scenario that the drones effectiveness will be built around. This scenario is the following

    An individual has been working on a powerline when suddenly the powerline comes crashing down. 
    The individual is unresponsive and paramedics cannot get to the individual due to the active powerline.
    The triage drone will be used to fly 20' away to the downed individual, attempt to communicate with 
    the individual, and read their vitals. The powerline and the individual are in a clear field 
    with no wind on a clear day.

  The specifications for this project have remained the same as our customer has not changed. This proect does not have many constraints. The following list describes the constraints as well as reasoning and reference numbers for each constraint.

  
**1.** The drone SHALL be user-friendly.  
**2.** The drone SHALL have an integrated system for security.  
**3.** The drone SHALL remain under 400 ft above ground level
**4.** The drone SHALL not exceed 100 mph
**5.** The drone SHALL be equipped with anti-collision lighting 




The fully formulated problem is the overall objective and scope complete with the set of shall statements. This was part of the project proposal. However, it may be that the scope has changed. So, state the fully formulated problem in the introduction of the conceptual design and planning document. For each of the constraints, explain the origin of the constraint (customer specification, standards, ethical concern, broader implication concern, etc).


## Comparative Analysis of Potential Solutions

In this section, various potential solutions are hypothesized, design considerations are discussed, and factors influencing the selection of a solution are outlined. The chosen solution is then identified with justifications for its selection.


## High-Level Solution

The solution to this problem rerquires an aviation drone as well as integrated sensors to record data. The drone will be manually flown to the victim and have the ability to hover 1 meter above the target. Attached to the drone will be a sensing system that can measure one's, heart rate and respiratory rate, and cognitiveness all without contacting the individual. The data gathered by the sensors will then be sent to the computing system. The information will be processed and the person will be catagorized by servereness of injuries in accordance with the START method. 

In order to do this, the design will be split up into devices:

1). Power device <br />
        -A battery will be used to supply all necessary power to each device along with voltage regulators to adjust the voltage to the required amount for each sensing device. The battery will be the input to the voltage regulator circuit. The output of the regulator circuit will be wired to the heartrate/ respiratory rate doppler, the voice detection system, and the computing system. 
        
2). Signal Processing <br /> 
        -This processing unit (Jettson Nano) will process the data recieved from the microphone as well as the data from the heartbeat and respiratory doppler. The information will then be compared to the START triage method and the results will be wirelessly tranmitted to the user interface. The processing unit will have serial or digital input lines coming from the doppler radar as well as an analog input line coming from the microphone. It will have a wireless radio frequency output going to the user control device. 
        
3). User Control <br /> 
    -After the signlas are processed the information will be sent to a telecommunication device that will transmit the victims vitals as well as triage level back to the user. The information will be shown on an LCD display at the controller. This device will have one radio frequency signal input that comes from the signal processing device. 
    
4). Cognitive test devise <br /> 
    -The user will have a button to allow a procedure to occur using a speaker and a microphone.The speaker will send out a call a prompt and and the microphon will capture audio data and relay it back to the computing system. 
    
5). Heartbeat/Respiratory dopper <br /> 
    -The doppler radar is responsible for obtaining heatbeat and respiratory rate frequencies. The data acquired will also be sent to the computing system. 




### Hardware Block Diagram

Block diagrams are an excellent way to provide an overarching understanding of a system and the relationships among its individual components. Generally, block diagrams draw from visual modeling languages like the Universal Modeling Language (UML). Each block represents a subsystem, and each connection indicates a relationship between the connected blocks. Typically, the relationship in a system diagram denotes an input-output interaction.

In the block diagram, each subsystem should be depicted by a single block. For each block, there should be a brief explanation of its functional expectations and associated constraints. Similarly, each connection should have a concise description of the relationship it represents, including the nature of the connection (such as power, analog signal, serial communication, or wireless communication) and any relevant constraints.

The end result should present a comprehensive view of a well-defined system, delegating all atomic responsibilities necessary to accomplish the project scope to their respective subsystems.


### Operational Flow Chart

Similar to a block diagram, the flow chart aims to specify the system, but from the user's point of view rather than illustrating the arrangement of each subsystem. It outlines the steps a user needs to perform to use the device and the screens/interfaces they will encounter. A diagram should be drawn to represent this process. Each step should be represented in the diagram to visually depict the sequence of actions and corresponding screens/interfaces the user will encounter while using the device.


## Atomic Subsystem Specifications

### **Drone controller subsystem**
#### **connections**
Bi-directional wireless communication to the drone and computing subsystem.
Output digital connection to LCD display.
Output power connection to LCD display.
Input connection to microphone.
Output connection to the speaker.
Digital wires to external buttons and switches.

#### **specifications**
The drone controller shall work in tandem with the drone to fly the drone.
The drone controller shall connect to the computing subsystem in order to display collected data.
The drone controller shall be conect to a microphone and speaker to ensure operator can talk to victim.
The drone controller shall connect to buttons and switches to control the signal processing and microphone.

#### **Description**
The drone controller will come out of the box with the drone and will be modified to have extra functionality. The drone controller shall connect to an LCD display and display the information from the computing subsystem. The controller will be modified to communicate with the computing subsystem wirelessly. The controller will need to have a power connection to the LCD as well. The controller subsystem will perform the logic neccessary to display the data to the LCD.
### **Power subsystem**
#### **connections**
The drone will mount the computing subsystem, microphone, and speaker.
Bi-directional wireless communication to the drone controller.

#### **specifications**
The drone shall weigh less than 20 lbs.
The drone shall be able to fly out of the box.
The drone shall be modular and able to add or change parts.
The drone shall have anti collision lighting.

#### **Description**
The drone will be bought and intended to fly out of the box. The drone needs to be able to be modified and extra parts added. A modular design is the most practical. The drone needs to have its own drone controller that comes with it. This will allow our team to spend more of our time on other parts of the project. 


### **Computing subsystem**
#### **connections**
Bi-directional wireless connection line between computing subsystem and the drone controller.
USB connection to extenal microphone.
analog signal to doppler sensor.
USB connection to speaker.

#### **specifications**
The Computing subsystem shall communicate via LoRaWAN to the drone controller and send signal data, voice data, and state data.
The Computing subsystem shall use signal processing to determine heart rate and respritory rate.
The Computing subsystem shall be able to get accurate readings from 1 meter away.
The Computing subsystem shall be able to use the microphone and speaker to communicate with the individual.
The Computing subsystem shall not store recordings except for use in transmitting to drone controller.
The Computing subsystem shall limit recorded voice between 80 Hz and 255 Hz.

#### **Description**

The Computing subsystem is the center of the sensor processing and communication. The system will connect to the drone and will interface the microphone, speaker, doppler, and drone controller. It will employ signal processing algorithms to extract useful information about the heart rate and respritory rate. The computing subsystem will connect wirelessly to the drone controller module and ensure that no audio information is recorded.

Based on the high-level design, provide a comprehensive description of the functions each subsection will perform.

Inclued a description the interfaces between this subsystem and other subsystems:
- Give the type of signal (e.g. power, analog signal, serial communication, wireless communication, etc).
- Clearly define the direction of the signal (input or output).
- Document the communication protocols used.
- Specifying what data will be sent and what will be received.

Detail the operation of the subsystem:
- Illustrate the expected user interface, if applicable.
- Include functional flowcharts that capture the major sequential steps needed to achieve the desired functionalities.

## Ethical, Professional, and Standards Considerations

In the project proposal, each team must evaluate the broader impacts of the project on culture, society, the environment, public health, public safety, and the economy. Additionally, teams must consider relevant standards organizations that will inform the design process. A comprehensive discussion should be included on how these considerations have influenced the design. This includes detailing constraints, specifications, and practices implemented as a result, and how these address the identified considerations.


## Resources

You have already estimated the resources needed to complete the solution. Now, let's refine those estimates.

### Budget

Develop a budget proposal with justifications for expenses associated with each subsystem. Note that the total of this budget proposal can also serve as a specification for each subsystem. After creating the budgets for individual subsystems, merge them to create a comprehensive budget for the entire solution.

### Skills

First, conduct a thorough analysis of the skills currently available within the team, and then compare these skills to the specific requirements of each subsystem. Based on this analysis, assign each team member to oversee the development of a particular subsystem. Additionally, appoint a different team member to take the specifications and generate a corresponding solution. Ensure that the assignments are structured in such a way that no single team member is simultaneously managing and being managed by the same person. If there are more team members than subsystems, consider further subdividing the solutions into smaller tasks or components, thereby allowing each team member the opportunity to manage and design a subsystem.

### Timeline

Revise the detailed timeline (Gantt chart) you created in the project proposal. Ensure that the timeline is optimized for detailed design. Address critical unknowns early and determine if a prototype needs to be constructed before the final build to validate a subsystem. Additionally, if subsystem $A$ imposes constraints on subsystem $B$, generally, subsystem $A$ should be designed first.


## References

[[1](#specification)]
“DARPA Triage Challenge,” triagechallenge.darpa.mil. https://triagechallenge.darpa.mil/

‌

## Statement of Contributions

Each team member is required to make a meaningful contribution to the project proposal. Ensure that each member's contributions are clearly documented.
