/*
 * Led.c
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */

#include "Led.h"

void LED_Init(uint8 portName, uint8 pinNum){
	Gpio_ConfigPin(portName, pinNum, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_NO_PULL_UP_DOWN);
	GPIO_WritePinValue(portName, pinNum, LED_OFF);
}

void LED_Activate(uint8 portName, uint8 pinNum, uint8 state){
	GPIO_WritePinValue(portName, pinNum, state);
}

void LED_Toggle(uint8 portName, uint8 pinNum){
	boolean state = GPIO_ReadPinState(portName, pinNum);
	GPIO_WritePinValue(portName, pinNum, !state);
}




