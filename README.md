Revolutionizing Post-Earthquake Operations with an Innovative Search and Rescue System, Powered by Smart Sensor Technology

## Project Description
Addressing the urgent need for innovative solutions in the aftermath of earthquakes, our project focused on enhancing search and rescue operations. Turkey, prone to seismic activities, experienced a devastating earthquake in Kahramanmaraş on February 6, 2023, resulting in over 45,000 casualties. 
The project aimed to overcome challenges faced by search and rescue teams in locating survivors trapped in debris with students from electrical and electronics engineering, mechatronics engineering, and computer engineering. Our multidisciplinary team is committed to developing a solution to improve post-earthquake search and rescue efficiency.

This project aimed to develop a system that can detect the location of survivors trapped in earthquake debris using smart sensor technology and wireless sensor networks. 
The project was done as a team work for the MECE 422 course at Atılım University which was held in the last semester of 4th grade
I was the team leader responsible for conducting every part of the research procedure.

## MATLAB and Arduino Code Details
The project involves modeling and simulation of the system behavior using MATLAB and Arduino. 
The MATLAB code implements the trilateration algorithm to calculate the coordinates of the survivor based on the distance measurements from four mmWave sensors. 
The Arduino code simulates the sensing and communication subsystem using mmWave sensors and Zigbee modules. The code also displays the calculated coordinates on an LCD screen and sends them over Zigbee communication to a remote receiver. The code files are available in the code folder of this repository.

## 3D Trilateration Algorithm Calculation Technique to Extract Survivor’s Location
The system uses a set of quadratic equations called trilateration to calculate the distances that have been measured. This method can locate the object with the tag on the XY plane and also determine its Z axis of human presence. The object’s position on the X, Y, and Z coordinate system can be found by using 3D trilateration.

<img width="446" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/6e290567-1b09-4bea-9d92-a85fc3e65456">

Figure B.1 shows a sensor reader that is added to the existing three. This extra reader allows us to measure the Z-axis component of the tagged object’s position. We can use linear algebra to calculate X, Y, Z locations using 3D trilateration. The red dot will represent the location of the survivor that is being searched for.  The reference nodes, also known as the sensors, are labeled A1, A2, A3 and A4, the distances between the reference nodes and the tagged node are labeled d1, d2, d3 and d4.  The intersection between all four nodes is the location of our unknown survivor location.   

The algorithm formulas for this method as follows:

<img width="280" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/65fa4323-31b0-4fb2-af6e-5fa1851795f9">

We can rewrite the previous equations as 3 linear equations.

<img width="646" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/deaaa6b1-a85c-4169-9fdd-55e0e8e7c698">

Then, we use Cramer’s rule inside the algortihm calculation to find the survivor locations in X,Y and Z components from Equation 1, Equation 2 and Equation 3. 

<img width="615" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/c35ba2e2-7f6c-4323-b4f0-4c541b13cb4e">
<img width="615" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/132beba5-2f06-4548-8488-83d00aa066b8">
<img width="615" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/f4760a15-cc7e-40ad-81d0-6e211952c94e">

## MATLAB Simulation
<img width="540" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/29e4fd41-18de-41dd-84f2-710e655e23a3">

As shown in Figure 7, a simulated environment has been made using MATLAB & Simulink. This simulation scatters 4 sensors inside the 3D environment of (X1, Y1, Z1) Cartesian Coordinates and places a human to be detected. The process begins by defining the global coordinates of each sensor in terms of (X1, Y1, Z1), along with the coordinates of the to be detected human. The sensors individually calculate the distance between them and the target human survivor in meters. These distances are registered as u1, u2, u3, and u4. A total of 2 readings for each sensor will give more accurate data by averaging the “u” values to the number of readings. A Trilateration Calculation is then made using the linear equations below. 

<img width="539" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/3510c10b-4529-452f-a030-d3935db0449c">


From these initial calculations, it is possible to derive the precise 3D coordinates by employing Cramer's rule, as detailed in the equations provided in Appendix B. By applying this method, the resulting (X1, Y1, Z1) coordinates in the global reference frame of the human can be accurately determined. For a more comprehensive comprehension of the implementation process, the corresponding code can be referred to in Appendix D, which offers a step-by-step breakdown of the methodology utilized. This code serves as a valuable resource for those seeking to delve deeper into the intricacies of the calculations involved and gain a thorough understanding of the underlying principles at work.

In these simulations, a human has been defined with coordinates of (-5.1, 10.9, -3). By running the simulation and observing the scope, these results can be found for the calculated coordinates in Figure 8 as follows.

<img width="375" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/fcb4039d-afe5-4d59-a2e1-142e395da38a">

Furthermore, a Scatter Plot has been made using MATLAB to simulate the environment can be observed below (code found in Appendix E). From what can be seen in Figures 8 and 9, the calculated coordinates are not 100% accurate to the actual ones. However, the highest offset is found to be less than 1 meter, which is acceptable in real-life application, as it is relative to the human body size. 


<img width="372" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/413c9689-8d3c-46a1-a783-32bda4d8cfc3">

# Arduino Simulation Result Comparison Between Measured and Calculated Real Data of the Survivor Location

<img width="597" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/47a9c859-a157-406a-87cc-7518d25a4dd3">

This indicates that the Arduino simulation successfully completed, as the calculated locations match the measured locations consistently with a slight tolerance due to the trilateration algorithm accuracy. The simulation accurately estimated the real location of the survivor throughout the experiment with the help of the 3D trilateration calculation, the fourth sensor is needed for the extra unknown z-component measurement. Therefore, based on the provided data, we can conclude that the Arduino simulation was successful in estimating the survivor's real location.

## Representation of Product/System Architecture
<img width="646" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/4eae91d0-9b38-4422-b91a-24bc1398fef8">

## Fishbone Root Cause Analysis Diagram
<img width="646" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/3443619e-54a9-4b65-bf2d-a3f9b11d2e37">

## Use-Case Diagram for the Project Design 
<img width="446" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/0f65b7c4-3283-4f58-883b-97ecda98a1f1">

# Project Timeline Table
<img width="570" alt="image" src="https://github.com/yektaparlak/Matlab-3D-Trilateration-Location-Estimation-Calculation-Technique/assets/111290340/bc0dc80c-e0cb-4f96-8ea4-ddac5b83e155">
