

## **Introduction**

&nbsp; Over the last ten years, drones have become ubiquitous in many ways. From warfare to marketing, drones have become cheaper alternatives to old problems and new solutions for emerging issues. In the effort to help first responders, drones can be used in many ways to help fight fires, locate lost persons, identify hazardous materials, and more.

&nbsp; Aviation drones have become useful tools for scanning areas that are too difficult or too dangerous to reach for first responders. Taking a step further, aviation drones can assist in assessing the servierity of an emergency situation. During a situation such as this, having a drone with sensors and AI capabilities can assess the medical conditions of the victims allowing first responders to prioritze the most affected areas. This would grant first responders the ability to use resources such as time and aid more effeciently, ultimately resulting in more lives saved. Currently, there are not any aviation drones that have the capability to catagorize victims of an emergency by prioritizy the critical injuries. Due to this problem the Defense Advanced Research Projects Agency(DARPA) has come up with a challenge to provide first responders with this described technology.
          -A drone with integrated cameras, sensors, and AI algorithms shall fly above the ground to quickly detect possible cassualties in large areas. 
          -The drone shall fly close to victims and use sensors to collect medical data about the injured person. 

&nbsp; In search and rescue missions, our drone could provide initial canvasing of an area to pinpoint locations of possible human sightings that could be followed up via helicopter or ground search team. Furthermore. our drone could help scan buildings to find the hottest part of the fire. This proposal will set out to outline a project that will build a drone to suit these objectives. In the coming sections, the specific goals and objectives will be laid out as well as specifications and constraints that our team will strive to overcome. Our team will also examine current solutions to this problem and other approaches and argue why our project is more effective.

## **Formulating the problem**

&nbsp; To build this drone, we must consider the scope of our project and the specific constraints we will be working with. One of the main problems we will encounter is the connectivity of the drone to the centralized position. This is necessary as the drones themselves will not have the processing power to make a full identification of a lost person. Rather, it would send back data of a possible sighting to be sifted through by the Fire Department. The drone would need to be able to track its location via GPS in order to not get lost as well as searching a target area. A large obstacle to be tackled is locating individuals through the tree canopy. Thermal imaging itself does not penetrate the tree canopy well. So more sophisticated approaches must be implemented. 

&nbsp;In addition to autonomous capabilities, the drone will be able to be manually controlled. This will provide more functionality to the drone. As we add equipment to the drone, it becomes heavier so our team will need to take care to get the lightest equipment possible while also reigning in our budget. Take will also have to be taken in order to safely charge the drone. Over charging Lithium Polymer batteries can be very dangerous. This is especially of concern as Li-Po batteries are a popular choice for drones.

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

## **Relevant Literature**

The IEEE website has multiple papers on this very topic, but the following specifically details the process of an unmanned vehicle being used for search and rescue (<https://ieeexplore.ieee.org/abstract/document/10434325>).

There are essentially 4 basic steps in the process:

- Receive sensor inputs
- Process the inputs
- Make a decision
- Actuate the mechanisms

How each is accomplished is decided by the engineering team.

### **Constraints**
(revisit below) hehe
#### Cost

- Min - $5,000
- Max - $13,000

#### Flight Time

- Min – 30 min
- Max – 65 min

#### Transmission Range

- Min – 7.5 miles
- Max – 12.4 miles

#### Weight

- Min – 1.06 lb
- Max – 4.72 lb

#### Other Properties

- Weather resistant (wind and rain resistance)
- Night vision capabilities

If our project is to be a success, our drone will need to excel at one of the previously mentioned areas and not fall too far below the others. More relevant specifications may be identified.

## **Set Goals**

#### 1. Ensure Cost-Effectiveness and Budget Optimization
**Objective:** Manage and allocate finances and budgeting to fully optimize the drone’s capabilities and performance.  
**Measurement:**
- How well the team tracks and accounts for each financial decision made throughout the project.
- How well the team’s capability of conducting an analysis comparing the cost of products to the benefits that will provide to the drone’s performance.

#### 2. Maximize Search and Rescue Capability
**Objective:** Enhance the capabilities of the drone making it more effective in search and rescue.
**Measurement:**
- How quickly the drone’s capability of targeting a lost individual and communicating the means of rescue back to the team.
- How effective the drone is in searching for lost individuals and locating across different terrains, elevations, and scenarios.

#### 3. Ensure Usability and Safety
**Objective:** Optimize the drones features to create a more user- friendly device that safely operates.
**Measurement:**
- The success rate of how well the drone’s ability to operate without failure.
- How easy and effective the drone’s operation is when operated by different users.
- How effective the instruction on the drone’s usage is.

## **Timeline and Resources**

<img width="1497" alt="Screenshot 2024-09-20 at 11 19 20 AM" src="https://github.com/user-attachments/assets/a383c1a6-6119-43ec-a3bc-588f8e763e80">

**Resources**

\- Drone  
\- Microprocessors  
\- Hardware  
\- Software  

## **Impacts of a search and rescue drone**

1) **Culture**

\- The development of drones in the use of search and rescue contributes to positive outlooks on technological advancement. Using drone technology to solve real-world problems by way of technology creates a culture of high-tech innovation.

2) **Society**

\- Aviation drones can be faster, and safer than the boots-on-the-ground method of search and rescue. A drone can access terrain that might be dangerous for humans to traverse, potentially saving lives. Along with increasing the sense of safety in communities it also unlocks new roles and responsibilities under an emergency services career.

3) **Environment**

\- Ground-based search and rescue operations can be disruptive to the natural environment. Aerial search and rescue operations by way of drones are less invasive and leave a smaller environmental footprint.

4) **Public Safety**

\- Search and Rescue drones allow for quick intervention and less risk to both the victim and rescue professionals. These factors contribute to a higher chance of a successful rescue.

5) **Economy**

\- Traditional search and rescue methods require expensive resources such as manpower, equipment, and fuel. On the other hand, search and rescue drones can allow for more cost-effective rescue plans.

\- The application of search and rescue drones can grow the drone and technological development industry. This would result in job opportunities and economic stimulation.


## **References**
[1] DARPA Triage Challenge. [Online]. Available: https://triagechallenge.darpa.mil/. [Accessed:
26-Jan-2024].
[2] “DTC: FAQ,” DTC | FAQ. [Online]. Available: https://triagechallenge.darpa.mil/faq.
[Accessed: 26-Jan-2024].



## **Statement of contribution**
