# Vehicle Door Handle Control Unit

## Table of contents:
- [Introduction](#introduction)
- [Project Features](#project-features)
- [Project Structure](#project-structure)
- [Application Preview](#Application-preview)
- [Requirements to run](#Requirements-to-run)
- [Run the project](#Run-the-project)
- [Team]()

***
### Introduction

The project aims to implement a vehicle door handle control unit that supports an anti-theft locking capability. The system consists 
of the following components:
   - A microcontroller unit.
   - Two push buttons, one to simulate the handle lock/unlock button, and the other one to simulate the door lock/unlock. 
   - Three LEDs, one to simulate the vehicle lock, one to simulate the hazard lights, and one for the ambient vehicle light.
   - All the push buttons are connected as active low.
   - All the LEDs are connected as active high.
     
***
### Project Features

**In this project, we have implemented:**
- [x] **GPT Driver (General Purpose Timers)**:
  > It support the three basic counting modes :
      1. `Up Counting`     : The GPT counts up from 0 to the maximum value of the counter register. When the counter reaches the 
                              maximum value, it overflows and starts counting from 0 again.
      2. `Down Counting`   : The GPT counts down from the maximum value of the counter register to 0. When the counter reaches 0, it 
                              underflows and starts counting from the maximum value again. 
      3. `Up-Down Counting`: The GPT counts up from 0 to (the maximum value of the counter register -1 ), and then counts down from the maximum 
                              value to 1. When the counter reaches 0, it starts counting up again. 
   - Time Base Unit includes :
     1.  

***
### Project Structure

- **The System Layers Design**:
  ![layers](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/73500759-4c90-41b2-8991-2675331aeaf0)


- **The system shall be implemented to handle the following use cases**:
  ![system](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/a192ff48-1264-4c14-8f41-4301ff52ecca)


- **The System Hardware Components** :
  - STM32F401x Microcontroller
  - Handles Push Button
  - Door Push Button
  - Vehicle Led ( Green )
  - Hazard Led  ( Red )
  - Ambient Led ( Blue )

- **Implemented Drivers** :
```
VehicleDoorHandle_ControlUnit
├─  Button
│  ├─ Button.c 
│  └─ Button.h
├─  Delay
│  ├─ Delay.c 
│  └─ Delay.h
├─  External_Interrupt
│  ├─ ExtI.c
│  ├─ ExtI.h
│  └─ ExtI_Private.h
├─  Gpio
│  ├─ Gpio.c
│  ├─ Gpio.h
│  └─ Gpio_Private.h
├─  GPT
│  ├─ gpt.c 
│  ├─ gpt.h
│  └─ GPT_Private.h
├─  Led
│  ├─ Led.c 
│  └─ Led.h
├─  Lib
│  ├─ Bit_Operations.h 
│  ├─ Std_Types.h
│  └─ Utils.h
├─  Rcc
│  ├─ Rcc.c 
│  ├─ Rcc.h
│  └─ Rcc_Private.h
├─  src
│  ├─ main.c 
│  ├─ VehicleDoorHandle.c
│  └─ VehicleDoorHandle.h

README.md
```
***
### Application Preview
<br>

- Steps:

| Action                            | Result                     |
|-----------------------------------|:--------------------------:|
|Handle Button Pressed              |  Handle Un-locked          | 
|Wait for 10 sec                    |  Automatic Handle Locked   | 
|Door   Button Pressed              |  `No Action`               | 
|Handle Button Pressed (2nd time)   |  Handle Un-locked          | 
|Door   Button Pressed (2nd time)   |  Door Opened               | 
|Handle Button Pressed (3rd time)   |  `No Action`               | 
|Door   Button Pressed (3rd time)   |  Door Closed               | 
|Handle Button Pressed (4th time)   |  Handle locked             | 
<br>

- Simulation:
![Final_Project_Embedded](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/75c308a2-dcc0-458f-a70b-243d7791c526)


***
### Requirements to run 
[Setups](https://github.com/omaranwar21/Vehicle-door-handle-CU/files/11805849/Setups.pdf)

### Run the project
[Create Project STM32F401 on Eclipse](https://github.com/omaranwar21/Vehicle-door-handle-CU/files/11805837/Create.Project.Stm.on.eclipse.pdf)

### Team

Second Semester - Embedded Systems  (SBE3240) class final project created by:

| Team Members' Names                                  | Section | B.N. |
|------------------------------------------------------|:-------:|:----:|
| [Omar Ahmed Anwer](https://github.com/omaranwar21)   |    2    |  2   |
| [Neveen Mohamed](https://github.com/NeveenMohamed)   |    2    |  49  |
