/*
 * Button.c
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */


#include "Button.h"

BUTTON_TimerState timerIsOn = BUTTON_TimerIsOff;

uint32 BUTTON_firstTime;

uint16 g_buttonsFlags = 0;

BUTTON_FirstRead firstRead_flag = BUTTON_FirstRead_NotDone;

void BUTTON_Init(uint8 portName, uint8 pinNum){

	SET_BIT(g_buttonsFlags, pinNum);

	Gpio_ConfigPin(portName, pinNum, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_PULL_UP);

}

BUTTON_States BUTTON_ReadState(uint8 portName, uint8 pinNum){

#ifdef GPT_H_
	static BUTTON_States first_read;

	uint32 elapsed_time;

	BUTTON_States second_read = BUTTON_FLOATING;

	if (firstRead_flag == BUTTON_FirstRead_NotDone) {

		if (timerIsOn == BUTTON_TimerIsOff) {

			GPT_StartTimer(TIM2,BUTTON_START_TIME_ms);

		}

		first_read = (BUTTON_States)GPIO_ReadPinState(portName, pinNum);

		if (first_read == BUTTON_PRESSED) {

			firstRead_flag = BUTTON_FirstRead_Done;

		}
		else {

			SET_BIT(g_buttonsFlags, pinNum);

			return BUTTON_RELEASED;

		}

		BUTTON_firstTime = GPT_GetElapsedTime(TIM2);

	}
	else{
		elapsed_time = GPT_GetElapsedTime(TIM2);

		if ( ( (elapsed_time - BUTTON_firstTime) >= BUTTON_DEBOUNCING_TIME_ms ) ) {

			second_read = (BUTTON_States)GPIO_ReadPinState(portName, pinNum);

			firstRead_flag = BUTTON_FirstRead_NotDone;

			if (first_read == second_read ) {

				 if (first_read == BUTTON_PRESSED &&  (((g_buttonsFlags >> (pinNum)) & 1) == BUTTON_PRESSED)) {

					 CLEAR_BIT(g_buttonsFlags, pinNum);

					return BUTTON_PRESSED;

				}

			}

		}

	}


#else

	if ((BUTTON_States)GPIO_ReadPinState(portName, pinNum)	== BUTTON_PRESSED ) {

		delay_ms(BUTTON_DEBOUNCING_TIME_ms); 	//Debouncing

		if ( ((BUTTON_States)GPIO_ReadPinState(portName, pinNum) == BUTTON_PRESSED) &&  (READ_BIT(g_buttonsFlags, pinNum) == BUTTON_PRESSED) ) {
			CLEAR_BIT(g_buttonsFlags, pinNum);
			return BUTTON_PRESSED;
		}
	}else {
		SET_BIT(g_buttonsFlags, pinNum);
	}

#endif

	return BUTTON_RELEASED;

}

