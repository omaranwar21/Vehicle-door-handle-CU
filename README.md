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

**In this project, we have:**
- [x] **Implemented GPT Driver (General Purpose Timers)**:
  - It support the three basic counting modes :
      1. `Up Counting`     : The GPT counts up from 0 to the maximum value of the counter register. When the counter reaches the 
                              maximum value, it overflows and starts counting from 0 again.
      2. `Down Counting`   : The GPT counts down from the maximum value of the counter register to 0. When the counter reaches 0, it 
                              underflows and starts counting from the maximum value again. 
      3. `Up-Down Counting`: The GPT counts up from 0 to (the maximum value of the counter register -1 ), and then counts down from the maximum 
                              value to 1. When the counter reaches 0, it starts counting up again.
         <br>
   - Time Base Unit includes :
      1.  Counter Register (TIMx_CNT)
      2.  Prescaler Register (TIMx_PSC)
      3.  Auto-Reload Register (TIMx_ARR)
         <br>
   - It provides functions to :
      1.  Initializes the GPT with the specified mode and counter direction.
      2.  Starts the GPT with the specified number of overflow ticks.
      3.  Checks whether the GPT has reached the specified time interval.
      4.  Returns the remaining time until the GPT overflows.
      <br> 
   - STM32 Timer Assembly (Block Diagram):
   - ![stm counter diagram](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/552de5cc-d0df-48bc-8ce3-130a76971bfc)
   <br>
- [x] **Implemented Button Driver Using Delay OR GPT For Debouncing Problem**:
  - Button bouncing is a common problem in embedded systems that can be solved by using a delay. This delay can be implemented using a for-loop 
    or a timer in a GPT. The for-loop method is simple but can consume processing power, while the timer approach is more efficient and precise 
    but requires more setup. The choice between the two depends on the system's specific requirements.
    ![debouncing](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/495f651a-0e26-402e-8738-a76ce9a0e4df)
  - It provides functions to:
     1. Initializes a button by setting the pin as an input and configuring the pull-up resistor. It also sets a flag to indicate that the button 
        is pressed.
     2. Reads the state of the button and also implements a debouncing algorithm to filter out spurious signals that can occur when the button is 
        pressed. The algorithm uses a **timer** OR **Delay** to measure the time between button presses and checks the button state twice to 
        ensure that it is stable. If the button state is stable, the function updates the button  flag and returns the button state.   
  - ![timer-delay](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/18d1349a-a7c7-478c-a3ce-a7d119af351e)
  - ![delay](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/bba9454d-013e-4b66-92f7-48dda989ed78)
      
<br>   
- [x] **Optimized The Use Of Flag Variables By Using Bit Field Structure**:
  - Using a single variable to represent multiple flags in an embedded system can reduce memory usage and simplify code, while also allowing for 
    simultaneous operations on multiple flags. However, proper synchronization and access control must be ensured to avoid issues.
    
  - ![bits](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/31c9d56f-ee91-4d47-b47b-f8ac923aef14)
   <br>

***
### Project Structure

- **The system follows Layered Architecture Style**:
  ![layers](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/73500759-4c90-41b2-8991-2675331aeaf0)


- **The system shall be implemented to handle the following use cases**:
  ![system](https://github.com/omaranwar21/Vehicle-door-handle-CU/assets/94166833/a192ff48-1264-4c14-8f41-4301ff52ecca)


- **The System Hardware Components** :
  - STM32F401x Microcontroller
  - Handle Push Button
  - Door Push Button
  - Vehicle Led ( Green )
  - Hazard Led  ( Red )
  - Ambient Led ( Blue )

- **Structure** :
```
Code
  ├─ VehicleDoorHandle_ControlUnit
  |  ├─  Button
  │  |   ├─ Button.c 
  |  │   └─ Button.h
  |  ├─  Delay
  |  │  ├─ Delay.c 
  │  |  └─ Delay.h
  |  ├─  External_Interrupt
  │  |  ├─ ExtI.c
  |  │  ├─ ExtI.h
  │  |  └─ ExtI_Private.h
  |  ├─  Gpio
  │  |   ├─ Gpio.c
  │  |   ├─ Gpio.h
  │  |   └─ Gpio_Private.h
  |  ├─  GPT
  │  |   ├─ gpt.c 
  │  |   ├─ gpt.h
  │  |   └─ GPT_Private.h
  |  ├─  Led
  │  |   ├─ Led.c 
  │  |   └─ Led.h
  |  ├─  Lib
  │  |   ├─ Bit_Operations.h 
  │  |   ├─ Std_Types.h
  │  |   └─ Utils.h
  |  ├─  Rcc
  │  |   ├─ Rcc.c 
  │  |   ├─ Rcc.h
  │  |   └─ Rcc_Private.h
  |  ├─  src
  │  |  ├─ main.c 
  │  |  ├─ VehicleDoorHandle.c
  |  |  └─ VehicleDoorHandle.h
  |  └─
  └─    
Simulation
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
