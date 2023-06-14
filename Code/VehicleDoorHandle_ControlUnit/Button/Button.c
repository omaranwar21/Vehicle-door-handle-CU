/*
 * Button.c
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */


#include "Button.h"

uint16 g_buttonsFlags = 0;

void BUTTON_Init(uint8 portName, uint8 pinNum){
	g_buttonsFlags |= (BUTTON_PRESSED << (pinNum));
	Gpio_ConfigPin(portName, pinNum, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_PULL_UP);

}

uint8 BUTTON_ReadState(uint8 portName, uint8 pinNum){
//	boolean first_read = GPIO_ReadPinState(portName, pinNum);
//	delay_ms(30); 	//Debouncing
//	boolean second_read = GPIO_ReadPinState(portName, pinNum);
//
//	if (first_read == second_read) {
//		if (first_read == BUTTON_PRESSED  ) {
////			g_buttonsFlags &= ~(BUTTON_RELEASED << (pinNum));
//			return BUTTON_PRESSED;
//		}else {
//			return BUTTON_RELEASED;
//		}
//	}else {
////		g_buttonsFlags |= (BUTTON_PRESSED << (pinNum));
//		return BUTTON_WEIRD_BEHAVIOR;
//	}

	if (GPIO_ReadPinState(portName, pinNum)	== BUTTON_PRESSED ) {

		delay_ms(30); 	//Debouncing

		if ( (GPIO_ReadPinState(portName, pinNum) == BUTTON_PRESSED) &&  (((g_buttonsFlags >> (pinNum)) & 1) == BUTTON_PRESSED) ) {
			g_buttonsFlags &= (BUTTON_RELEASED << (pinNum));
			return BUTTON_PRESSED;
		}
	}else {
		g_buttonsFlags |= (BUTTON_PRESSED << (pinNum));
	}
	return BUTTON_RELEASED;
}

