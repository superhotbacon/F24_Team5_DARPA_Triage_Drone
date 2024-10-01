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

