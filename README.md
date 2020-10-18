# Rubiks Cube Solver

<img src= "https://github.com/stevenfans/Rubiks-Cube/blob/master/images/group.JPG" width = "400">
Left to right: Steven Phan, Jose Melgar-Urrutia, Benjamin Adinata, Jonic Mecija

CSULB 490: Computer Engineering Senior Project Design


## Overview

<img src = "https://github.com/stevenfans/Rubiks-Cube/blob/master/images/logo.png" width = "300">

The Rubik’s Cube Solver provides a quick solution to an average person’s painstaking journey to solve a Rubik’s cube. With the use of computer software, robotic arms, and color identification, the product solves a 3x3 Rubik’s cube within 2 minutes or less.

## Hardware
<img src="https://github.com/stevenfans/Rubiks-Cube/blob/master/images/hardware2.JPG" width = 400>
Early stages of motor movement: https://www.youtube.com/watch?v=0SeQ-YWIk74

Main hardware components used:
- TM4C123GH Microcontroller
- Raspberry Pi Zero
- NEMA 17 Stepper Motors
- DRV8825 Motor Drivers

### Breadboard power circuit
<img src="https://github.com/stevenfans/Rubiks-Cube/blob/master/images/hardware1.JPG" width = 400>

### Early soldering board prototype for motor drivers
<img src="https://github.com/stevenfans/Rubiks-Cube/blob/master/images/solder.JPG" width = 300>

### Final PCB layout for all connections 
<img src="https://github.com/stevenfans/Rubiks-Cube/blob/master/images/pcb.JPG" width = 300>

## Software

### Software Flow Chart
<img src="https://github.com/stevenfans/Rubiks-Cube/blob/master/images/softwareFlow.png" width = 450>

### Solving Algorithm
Our solving algorithm uses the Two-Phase-Method, which allows us to solve the cube in as few steps as possible. This algorithm works by first getting the cube to contain a certain property, such as the first 2 layers are solved. Then the next phase would be to solve the last layer. The algorithm decreases the number of moves by first searching for moves to get to the first phase. It then generates and compares moves to solve the second phase to get it as low as possible.

### UART Communication Protocol
Using UART we create our own checksum protocol to ensure that the instructions being sent from the Raspberry Pi to the TM4C are the right ones being received. The pins of the microcontroller will then send signals to the DRV8825 driver chips. The turn instructions are sent between the start and stop bits. 

### Diagram of the UART Instructions Used
<img src="https://github.com/stevenfans/Rubiks-Cube/blob/master/images/UART.png" width = 250>


