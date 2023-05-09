/*
 * Button.c
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */


#include "Button.h"

uint16 buttonsFlags = 0;

void BUTTON_Init(uint8 portName, uint8 pinNum){
	buttonsFlags |= (BUTTON_PRESSED << (pinNum));
	Gpio_ConfigPin(portName, pinNum, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_PULL_UP);

}

uint8 BUTTON_ReadState(uint8 portName, uint8 pinNum){
	if (GPIO_ReadPinState(portName, pinNum)	== BUTTON_PRESSED ) {

		delay_ms(30); 	//Debouncing

		if ( (GPIO_ReadPinState(portName, pinNum) == BUTTON_PRESSED) &&  (((buttonsFlags >> (pinNum)) & 1) == BUTTON_PRESSED) ) {
			buttonsFlags &= (BUTTON_RELEASED << (pinNum));
			return BUTTON_PRESSED;
		}
	}else {
		buttonsFlags |= (BUTTON_PRESSED << (pinNum));
	}
	return BUTTON_RELEASED;
}

