## Introduction 

In mass casualty incidents (MCIs), where the number of injured individuals far exceeds the capacity of available medical resources, timely and accurate triage becomes critical to save lives. With the help of technology and innovation, triage can be much more manageable during a disaster. The DARPA Triage Challenge aims to engineer new designs and innovations to identify injured victims in a catastrophe helping first responders perform scalable, timely, and accurate triage [DARPA Triage Challenge, 2023 [1] ]. Considering this, a system of highly designed sensors integrated into an aviation drone will allow for the utmost effectiveness. The equipped aviation allows for rapid evaluation of a disaster situation, through real-time data collection and analysis. 
  
  With the help of a carefully engineered system of sensors carried by an aviation drone, it is achievable to deliver accurate and timely triage to these situations with limited medical resources. Therefore, to address the difficulty of this critical lifesaving challenge, a comprehensive and high-level design is essential for success. This detailed design will outline the key aspects necessary to overcome this challenge. 


## Introducing the problem


The problem proposed is to create a system that will manually fly to individuals in an emergency situation and read vital signs in terms of heart rate, respiratory rate, and cognition. Then the system must relay that information back to the user and rank the victim in terms of the START triage method. 
To understand the scope of the problem, the customer has outlined a specific scenario that the drone's effectiveness will be built around. This scenario is the following

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

### 1. Drone Design
  The drones considered for the solution: **Multi-Rotor Drone** & **Hybrid Drone**.

#### **Multi-Rotor Drone** [2]
 [](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.jouav.com%2Fproducts%2Fph-25.html&psig=AOvVaw2NoXoxPRNUwAb-XI9PWE50&ust=1729826904568000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCLCQvdSapokDFQAAAAAdAAAAABAI)![image](https://github.com/user-attachments/assets/ef86cd8d-5090-413c-971c-77160f0fdbe3)  
**Description:** A light-framed, vertical takeoff and landing (VTOL), multi-rotor drone.
  
**Pros:** High Payload Capacity, Vertical Takeoff and Landing Capability, Improved Control and Stability, Maneuverability, Cost-Friendly, Versatile, and Easy Storage.   
**Cons:** Limited Flight Time, Limited Range, Weather Sensitivity, Battery Usage, and Slow Flight speeds.  

#### **Hybrid Drone** [3]
[](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.viewprouav.com%2Fcompare%2F%3Fpost_id%3D3542&psig=AOvVaw16fp1WDzkosiA_6tgQ8p_V&ust=1729829283785000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCNj7tbOSpokDFQAAAAAdAAAAABAh)![image](https://github.com/user-attachments/assets/ed79ac40-2bc8-4f6f-a6a8-abf6501a5d0b)


**Description:** A VTOL and fixed-winged drone.  
  
**Pros:** High Payload Capacity, Fast Flight Speeds, High Range, Versatility, Fuel-Efficient, Extended Flight times.   
**Cons:** High Cost, Heavy Weight, Complex Flight Style, Higher risk of Malfunction, and Difficult to store.  
  
#### Drone Design Solution: 
Considering both the Pros and Cons of each drone, it is in the best interest of the solution to select the multi-rotor Drone. Budgeting and reliability played crucial roles in the decision-making. The multi-rotor drone allocated well with the team’s budget and created no conflicts with any other budgeting needs. For fast and accurate triage, it is a necessity to have a reliable drone, the multi-rotor drone seemed to have excelled in this category compared to the Hybrid drone. After careful consideration, the multi-rotor drone is the most optimal choice. 

*The photos above are for reference*

 
### 2. Computing Systems 
The computing systems considered were a **Raspberry Pi** and a **NVIDIA Jetson Nano** for the triage sensor system.  
#### **Raspberry Pi**  
**Description:** Small, Low-Cost Computing Device.  
**Pros:** Cost-Friendly, Compact Size, Customizable, Low Power Consumption, and Versatility.  
**Cons:** Low-Performance Capabilities, Limited storage, Overheating, and Limited Connectivity.  
#### **NVIDIA Jetson Nano** 
**Description:** Small, powerful, and comprehensive computing system.  
**Pros:** AI capabilities, High performance, Expandable Storage, Graphics processing optimization, and Multiple I/O options.  
**Cons:** Power Consumption, Larger Size, Lack of built-in Wi-Fi, Complexity, and High Cost.  
  
#### Computing Systems Solution:
Considering both the Raspberry Pi and the NVIDIA Jetson Nano, the Jetson Nano is the best solution for a computing system. With its high-performance capabilities in graphics processing,  it is a necessity due to the on-board camera that will be used during triage. It also allows for more I/O options compared to the Raspberry Pi, making it the essential choice considering the number of sensors and systems needed for timely and accurate triage. Despite the higher cost of the Jetson Nano, it is capable of maintaining the project budget with the Jetson Nano, making it the clear choice. 

    


## High-Level Solution

The solution to this problem requires an aviation drone as well as integrated sensors to record data. The drone will be manually flown to the victim and have the ability to hover 1 meter above the target. Attached to the drone will be a sensing system that can measure one's, heart rate and respiratory rate, and cognitiveness all without contacting the individual. The data gathered by the sensors will then be sent to the computing system. The information will be processed and the person will be categorized by severity of injuries in accordance with the START method. 

In order to do this, the design will be split up into devices:

1). Power device <br />
        -A battery will be used to supply all necessary power to each device along with voltage regulators to adjust the voltage to the required amount for each sensing device. The battery will be the input to the voltage regulator circuit. The output of the regulator circuit will be wired to the heartrate/ respiratory rate doppler, the voice detection system, and the computing system. 
        
2). Signal Processing <br /> 
        -This processing unit (Jettson Nano) will process the data recieved from the microphone as well as the data from the heartbeat and respiratory doppler. The information will then be compared to the START triage method and the results will be wirelessly tranmitted to the user interface. The processing unit will have serial or digital input lines coming from the doppler radar as well as an analog input line coming from the microphone. It will have a wireless radio frequency output going to the user control device. 
        
3). User Control <br /> 
    -After the signlas are processed the information will be sent to a telecommunication device that will transmit the victims vitals as well as triage level back to the user. The information will be shown on an LCD display at the controller. This device will have one radio frequency signal input that comes from the signal processing device. 
    
4). Cognitive test device <br /> 
    -The user will have a button to allow a procedure to occur using a speaker and a microphone. The speaker will send out a call a prompt and and the microphon will capture audio data and relay it back to the computing system. 
    
5). Heartbeat/Respiratory doppler <br /> 
    -The doppler radar is responsible for obtaining heartbeat and respiratory rate frequencies. The data acquired will also be sent to the computing system. 




### Hardware Block Diagram

[Hardware Block Diagram.pdf](https://github.com/user-attachments/files/17580758/Hardware.Block.Diagram.3.pdf)



The above URL contains the hardware block diagram using visio software. It details visually how we are splitting up our systems.


### Operational Flow Chart
[Operational Flow Chart.pdf](https://github.com/user-attachments/files/17498367/Operational.Flow.Chart.pdf)

The above pdf contains the rudimentary operational flow chart. It details how a user will operate the final product specific to the decisions he or she makes while using it.


## Atomic Subsystem Specifications

### **Programmable Drone subsystem**
#### **connections**
The drone will be wirelessly connected to a controller that flies the drone. 
The drone will also be wirelessly connected to an LCD screen. 
The drone's telecommunication system will be connected to the signal processing system. 


#### **specifications**
The drone shall accomplish all functionality from at least one meter away from the subject.  
The drone shall be able to operate at full performance for at least 15 minutes.  
The drone shall weigh less than 20 pounds even after the team makes modifications to the drone.  
The drone shall operate during daylight hours on a clear day with no wind.  


#### **Description**
The drone will be bought and be ready to fly. Senors and a proccessing unit will be added to the drone to expand the capabilities of the drone. The drone will be able to fly to a victim and use the attached sensors to check vitals and cognitivness and sort the injured person into a triage catagory. 

![Drawing.vsdx - Google Chrome 10_30_2024 6_29_08 PM](https://hackmd.io/_uploads/rydsWHg-kg.png)


### **Power and circuity design subsystem**
#### **connections**
Power signal to connect the signal processing subsystem

#### **specifications**
The power subsystem shall supply ample power to all needed subsystems.  
  The power subsystem shall optimally use the battery on the drone to prevent unnecessary discharge.  
  The power subsystem shall not have exposed wiring to ensure safety.  
  The power subsystem shall protect client circuits with fuses.  

#### **Description**
The power subsystem will be responsible for converting power from the battery to the signal processing subsystem subsystem and other perihperals on the drone. The following flow chart describes the steps to meet the specifications.


<img width="118" alt="power subsystem" src="https://github.com/user-attachments/assets/e48fe624-972f-47ee-875b-66390ba27317">

### **Signal Processing subsystem**
#### **connections**
  Digital connection to programmable Drone.  
    Digital signal to the doppler sensor.

#### **specifications**
  The signal processing subsystem shall use signal processing to determine heart rate and respiratory rate.  
  The signal processing subsystem shall be able to get accurate readings from 1 meter away.  
  The signal processing algorithms shall process data and have it ready to transmit within 500ms of being received.  

#### **Description**

The signal processing subsystem carries the heart of the project. It will employ signal processing algorithms to extract useful information about the heart rate and respritory rate. The subsystem will have to be fast and accurate. The system will connect data to the drone so that the drone can transmit the data back to the pilot. The following flow chart describes the steps to meet the specifications.

<img width="433" alt="Computing system (1)" src="https://github.com/user-attachments/assets/080f6b0c-3eb2-43e6-9002-d479ab09ed63">


### **Vitals' Sensor subsystem**

#### **connections**
The vitals' sensor will be wired to the signal processing subsystem on board the drone. It will be communicating digitally, most likely, via serial communications. It will be sending data to the signal processing subsystem that is has acquired through no-contact radar sensing.

#### **specifications**
The subsystem shall be operational from a distance of at least one meter.  
The subsystem shall detect a heart rate.  
The subsystem shall detect a breathing rate.  
The subsystem shall weigh less than half a pound.  
The subsystem shall not pose any threat to its subject.  

#### **Description**
The subsystem comprises of a radar doppler, likely of continuous wave (CW) type. It will send a periodic radio signal and listen for that same signal. Measuring how out of phase the sending and receiving signals are, the subsystem will provide the data required to compute the frequency of the breathing and heart rate of the subject. It will be paired with circuitry to filter noise and other disruptive signals.

### Interfacing Subsystem
#### **connections**
Wireless connection between drone and client computer.  

#### **specifications**
This system shall display data from the signal processing subsystem onto a laptop screen.  
This system shall use the wireless capability of the programmable drone.  
This system shall run a program on a laptop that will allow the laptop to connect to the drone.  

#### **Description**
This subsystem will utilize the programmable nature of the drone to connect to a laptop and display heart rate and breathing rate information onto the screen. This subsystem will need to write a program on the laptop in order to connect to the drone as well. This program should be portable between computer to computer. 

<img width="121" alt="Drawing (1)" src="https://github.com/user-attachments/assets/0d697553-49c6-4af9-b213-ad698e1283d0">

### **Microphone and speaker subsystem**

#### **connections**
Digital connection to the microphone from the drone.
Digital connection to the speaker from the drone.

#### **specifications**
The subsystem shall ensure two-way communication from the pilot to the victim.  
The subsystem shall communicate wirelessly via the drone.  

#### **Description**

The microphone and speaker subsystem is extremely important as it allows the pilot to determine the cognitive ability of the triage patient. This subsystem will have to figure out how the microphones will connect to the drone and the drone controller and figure out how to send data through the interfaces with the drone.

## Ethical, Professional, and Standards Considerations
1.	Culture  
\-	The integration of drone technology and medical resource contributes to a positive outlook on technological advancement. Using this drone technology to create better solutions to the world's needs creates a lasting culture of high-tech engineering and innovation. 

2.	Society  
\-	Integrating drones and robotics into the medical field with accuracy and effectiveness unlocks the potential of new roles and jobs for the future of society. Along with increasing the sense of safety between Humans and Robotics. 

3.	Environment  
\-	A Triage drone may allow for remote access to difficult areas, otherwise requiring invasive equipment that may damage sensitive ecosystems and environments. It also minimizes carbon emissions by reducing the need for ground transportation in  disaster-ridden areas. Therefore, it is considered that a drone may be very Eco-Friendly. 

4.	Public Health and Safety  
\-	A Triage integrated drone allows for a more accurate and timely response to a disaster site with an excessive amount of medical need and attention. It also considers the safety of the first responders preventing them from being in unsafe areas and conditions. Therefore, maximizing the effort and efficiency of the first responders. 

5.	Economy  
\-	The affordability of a Triage Drone system can greatly cut the cost of required resources that some economies may not be able to afford in the time of a disaster. The increased use of drones in situations may create demand for this industry leading to new jobs and economic growth. 

**START Adult Triage Method** [4]     
During times of disaster, good ethical decisions and considerations are often compromised. However, the START Method can better the decision-making for individuals in these situations. The Drone’s Triage system considers the START Method, thus influencing the design and selection of each subsystem to easily navigate the START Method for better and more ethical  life-saving decisions.
[](https://www.google.com/url?sa=i&url=https%3A%2F%2Fchemm.hhs.gov%2Fstartadult.htm&psig=AOvVaw0y8xkEmUV6EMQKV7fnoMyg&ust=1729839169189000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCLDd8Ju3pokDFQAAAAAdAAAAABAE)![image](https://github.com/user-attachments/assets/3f9fa7fc-3093-4bae-8b61-276a595ef9d1)  
These specifications were influenced greatly by the method above.  
1. The system shall obtain the presence of a heartbeat and its frequency. (range 0.45 to 2.92Hz).
2. The system shall obtain the breathing rate and frequency (range 0.13 to 1 Hz).
3. The system shall give vocal commands using the speaker and listen for responses to evaluate the cognitive ability of a victim.
4. The system shall display triage results and vitals wirelessly.




## Resources

You have already estimated the resources needed to complete the solution. Now, let's refine those estimates.

### Budget

[Cost Break Down.pdf](https://github.com/user-attachments/files/17501343/Cost.Break.Down.pdf)

The following budget was obtained from the previous Capstone group, and adjustments have been made by adding additional items that are anticipated to be required to complete our project.

### Skills

The team is comprised of three electrical engineers (Caleb Bucher, Chris Bradley, Reese Gilbert) and two computer engineers (Gabriel Buckner, Mathias Hagewood). Below are the specific specializations of each team member:

Caleb Bucher
- Software (python, SQL, C++)
- Solidworks
- Circuits/LTSpice
- PLC
- Project Management

Chris Bradley
- LTSpice
- Power Analysis
- Software (C & C++)
- Microcomputer Systems
- Soldering 

Reese Gilbert
- Circuits/LTSpice
- Power Analysis
- VHDL Programming
- Combinational Logic  

Gabriel Buckner
- Embedded Systems
- FPGAS & Digital System Design
- Signals and Systems
- Computer Networks
- Electromagnetic Interference

Mathias Hagewood
- Software (python, SQL, C/C++)
- Machine Learning (PolyRegression, NN)
- Embedded Systems
- Combinational Logic

In a similar vein, the project has been divided into simpler chunks to organize the engineering effort; these are listed in the above section titled "High-Level Solution". Based on each team member's specialty, interest, and workload, the project has been divided in the following way.

The power device will be researched and primarily developed by Reese Gilbert due to his specialization in power systems. Chris Bradley will be observing and acting as Reese's customer because of their similar expertise.

Gabriel Buckner and Mathias Hagewood will be heading the signal processing aspect, specifically the communication between the sensors and the jetson nano. This fits well with their experience in embedded systems and Gabriel's experience in signal processing. Caleb Bucher will be observing and acting as Gabriel's and Mathias's customers to ensure their work fits the team's vision.

Caleb Bucher and Chris Bradley will be developing the controller, its user interface, and the cognitive test device as these two modules go hand in hand. Their circuit, programming, and microcomputer expertise will be required to complete this task. Reese Gilbert and Mathias Hagewood will be observing and acting as customers due to their similar experience in circuitry.

Lastly, Reese Gilbert, Caleb Bucher, and Mathias Hagewood will innovate the vitals sensor. Reese's combinational logic experience, Caleb's circuit design experience, and Mathias's software experience will all be required to develop this technology. Gabriel Buckner will be observing and acting as a customer due to his expertise in signals and embedded systems.

These are the primary roles of each team member. If any new information is gathered on a subsystem, the roles are liable to change if someone's expertise becomes better aligned or under the advisement of the Georgia Tech team.

### Timeline

Revise the detailed timeline (Gantt chart) you created in the project proposal. Ensure that the timeline is optimized for detailed design. Address critical unknowns early and determine if a prototype needs to be constructed before the final build to validate a subsystem. Additionally, if subsystem $A$ imposes constraints on subsystem $B$, generally, subsystem $A$ should be designed first.


## References

[[1](#specification)]
“DARPA Triage Challenge,” triagechallenge.darpa.mil. https://triagechallenge.darpa.mil/  
[[2](#comparativeanalyisofpotentialsolution)] "JOUAV." [Online]. Available: https://www.jouav.com/products/ph-25.html  
[[3](#comparativeanalyisofpotentialsolution)] "VIEWPRO." [Online]. Available:
https://www.viewprouav.com/compare/?post_id=3542  
[[4](#ethics)] "START Adult Triage Method." [Online]. Available:
https://chemm.hhs.gov/startadult.htm
‌

## Statement of Contributions

- **Caleb Bucher**: Responsible for developing the hardware block diagram, managing the project budget, and creating the statement of contribution.

- **Chris Bradley**: Tasked with writing the introduction, overseeing document formatting, addressing ethical considerations, and conducting the comparative analysis.

- **Mathias Hagewood**: In charge of creating the operational flow chart and identifying necessary skills for project execution.

- **Reese Gilbert**: Focused on outlining the high-level solution and restating the problem.

- **Gabriel Buckner**: Responsible for defining the atomic subsystem specifications, managing resource allocation, and developing the project timeline.
