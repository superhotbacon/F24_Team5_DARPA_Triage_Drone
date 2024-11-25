
# Signal Processing Detailed Design


## General Requirements for the Document

The document should include:

- Explanation of the subsystem’s integration within the overall solution
- Detailed specifications and constraints specific to the subsystem
- Synopsis of the suggested solution
- Interfaces among different subsystems
- 3D models of customized mechanical elements*
- A buildable diagram*
- A Printed Circuit Board (PCB) design layout*
- An operational flowchart*
- A comprehensive Bill of Materials (BOM)
- Analysis of crucial design decisions
- Execution plan considering skill sets and time requirements
*Note: These technical documentation elements are mandatory only when relevant to the particular subsystem.


## Function of the Subsystem

The signal processing subsystem's purpose is to take the data gathered from the doppler radar and obtain the heart rate and respiratory rate from the signal. Within the entire drone, the signal processing subsystem serves as a middleman between the programmable drone subsystem and the sensors subsystem. This subsystem will be primarily on a Jetson Nano. The Jetson Nano will be part of the Microphone and Video subsystem, Signal Processing subsystem, and the programmable drone subsystem. Because all of these subsystems will be using the Jetson Nano, it is important that the algorithms used in this subsystem are powerful and computationally efficient. 


## Specifications and Constraints

This section should provide a list of constraints applicable to the subsystem, along with the rationale behind these limitations. For instance, constraints can stem from physics-based limitations or requirements, subsystem prerequisites, standards, ethical considerations, or socio-economic factors.

The team should set specifications for each subsystem. These specifications may require modifications, which must be authorized by the team. It could be necessary to impose additional constraints as further information becomes available.

Every subsystem must incorporate at least one constraint stemming from standards, ethics, or socio-economic factors.

  -The signal processing subsystem SHALL use signal processing to determine heart rate (range 0.45 to 2.92Hz) and respiratory rate (range 0.13 to 1 Hz). This specification stems from the subsystem prerequisites that allow the drone to work as intended.
  -The signal processing subsystem SHALL be able to get accurate readings from 1 meter away. This specification stems our customer, Georgia Tech Research Institute. This allows the drone to read the vitals of the victim without risking hurting the individual. Or in the possible case that the victim is inaccessible and can only be seen from 1 meter away.
 -The signal processing algorithms SHALL process data and have it ready to transmit within 500ms of being received. This specification stems from prerequisites that ensure the timely display of results so the operators can make quick decisions in high stress situations. 



## Overview of Proposed Solution

Describe the solution and how it will fulfill the specifications and constraints of this subsystem.

Extensive research has gone into the use of doppler radars over the last decade[1]. A lot of this research has been solving multiple issues with contactless monitoring such as movement artifacts from personal movement, motion artifacts from doppler movement, monitoring multiple people, and more. The two main choices are CW (continuous wave) and FMCW (frequency modulated continuous wave). Continuous wave is not able to find the distance of the object, only the change in distance. While this is suitable for the this project. Research indicates that FMCW dopplers are able to reduce motion artifacts associated with doppler movement with the addition of an accelerometer to measure this movement [2].


## Interface with Other Subsystems

Provide detailed information about the inputs, outputs, and data transferred to other subsystems. Ensure specificity and thoroughness, clarifying the method of communication and the nature of the data transmitted.


## 3D Model of Custom Mechanical Components

Should there be mechanical elements, display diverse views of the necessary 3D models within the document. Ensure the image's readability and appropriate scaling. Offer explanations as required.


## Buildable Schematic 

Integrate a buildable electrical schematic directly into the document. If the diagram is unreadable or improperly scaled, the supervisor will deny approval. Divide the diagram into sections if the text and components seem too small.

The schematic should be relevant to the design and provide ample details necessary for constructing the model. It must be comprehensive so that someone, with no prior knowledge of the design, can easily understand it. Each related component's value and measurement should be clearly mentioned.


## Printed Circuit Board Layout

Include a manufacturable printed circuit board layout.


## Operational Flowchart

For sections including a software component, produce a chart that demonstrates the decision-making process of the microcontroller. It should provide an overview of the device's function without exhaustive detail.


## BOM

A complete list of all components needed for the design must be given with the cost of each component and the total cost of the subsystem. The BOM should be a markdown table. Make sure to to provide the manufacteror, part number, distributor, distributor part number, quantity, and price. Also provide a url where the product can be purchased from. If the componenet is refernced on your schematic make sure to include the component name.

Provide a comprehensive list of all necessary components along with their prices and the total cost of the subsystem. This information should be presented in a tabular format, complete with the manufacturer, part number, distributor, distributor part number, quantity, price, and purchasing website URL. If the component is included in your schematic diagram, ensure inclusion of the component name on the BOM (i.e R1, C45, U4).

## Analysis

Deliver a full and relevant analysis of the design demonstrating that it should meet the constraints and accomplish the intended function. This analysis should be comprehensive and well articulated for persuasiveness.

## References

[1] C. Gu, “Short-Range Noncontact Sensors for Healthcare and Other Emerging Applications: A Review,”  _Sensors_, vol. 16, no. 8, p. 1169, Jul. 2016, doi: https://doi.org/10.3390/s16081169.

[2] I. Mostafanezhad, E. Yavari, O. Boric-Lubecke, V. M. Lubecke, and D. P. Mandic, “Cancellation of Unwanted Doppler Radar Sensor Motion Using Empirical Mode Decomposition,”  _IEEE Sensors Journal_, vol. 13, no. 5, pp. 1897–1904, May 2013, doi: https://doi.org/10.1109/jsen.2013.2238376.

‌‌[3] G. M. Brooker, “Understanding Millimetre Wave FMCW Radars ,” Nov. 21, 2005. https://www.researchgate.net/profile/Graham-Brooker/publication/228979037_Understanding_millimetre_wave_FMCW_radars/links/02e7e514a21ca686df000000/Understanding-millimetre-wave-FMCW-radars.pdf (accessed Nov. 25, 2024).

‌
