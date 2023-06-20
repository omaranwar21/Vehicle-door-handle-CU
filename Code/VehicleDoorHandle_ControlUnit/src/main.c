/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */

#include "VehicleDoorHandle.h"

uint32 first_time = 0;

VDH_Flags allFlags;

int main(void) {
	VDH_defaultState();

//	GPT_StartTimer(TIM3,2000);
//	Capture_Compare(TIM3);



	while(1){

//		uint8 flag= Capture_Compare_Flag;
//
//		if(flag== 1){
//			LED_Activate(VDH_LEDS_PORT, VDH_TEST_TIMERS_LED, LED_ON);
//		}

//		if(GPT_GetElapsedTime(TIM3) >= 1000){
//			LED_Activate(VDH_LEDS_PORT, VDH_TEST_TIMERS_LED, LED_ON);
//		}

		if (BUTTON_ReadState(VDH_BUTTONS_PORT, VDH_HANDLE_LOCK_UNLOCK_BUTTON) == BUTTON_PRESSED && allFlags.combinedFlags.door != VDH_DOOR_IS_OPENED) {
		LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_ON);

			timerIsOn = BUTTON_TimerIsOn;

			if(allFlags.combinedFlags.handle == VDH_HANDLE_FLOATING_STATE){
				allFlags.combinedFlags.handle = VDH_HANDLE_IS_LOCKED;
			}

			if (allFlags.combinedFlags.handle == VDH_HANDLE_IS_LOCKED) {
				allFlags.combinedFlags.handle = VDH_HANDLE_IS_UNLOCKED;
			}
			else {
				allFlags.combinedFlags.handle = VDH_HANDLE_IS_LOCKED;
				allFlags.combinedFlags.door_changeState = VDH_ACTION_IS_NOT_DONE;
			}

			VDH_stateAllLeds(LED_ON);

			allFlags.combinedFlags.end_action = VDH_ACTION_IS_NOT_DONE;

			allFlags.combinedFlags.timer_10SecFlag = VDH_10SEC_NOT_ELAPSED;

			allFlags.combinedFlags.doorUnlock_action = VDH_ACTION_IS_NOT_DONE;


			GPT_StartTimer(TIM2,VDH_SECURITY_TIME_IN_ms);

			first_time = GPT_GetElapsedTime(TIM2);

#ifdef EXTI_H_
			Exti_Enable(VDH_DOOR_LOCK_UNLOCK_BUTTON);
#endif

		}


		if (allFlags.combinedFlags.handle == VDH_HANDLE_IS_UNLOCKED) {
			if (allFlags.combinedFlags.doorUnlock_action == VDH_ACTION_IS_NOT_DONE) {
				VDH_doorUnlock();
			}
#ifndef EXTI_H_
			if (BUTTON_ReadState(VDH_BUTTONS_PORT, VDH_DOOR_LOCK_UNLOCK_BUTTON) == BUTTON_PRESSED) {

				VDH_doorButtonPressed();
			}
#endif
			if ((allFlags.combinedFlags.door == VDH_DOOR_IS_CLOSED) && (allFlags.combinedFlags.door_action == VDH_ACTION_IS_NOT_DONE)) {

				VDH_doorIsClosed();

			}
			if (GPT_CheckTimeIsElapsed(TIM2) == GPT_Elapsed && allFlags.combinedFlags.timer_10SecFlag == VDH_10SEC_NOT_ELAPSED
					&& allFlags.combinedFlags.door == VDH_DOOR_IS_CLOSED  && allFlags.combinedFlags.door_changeState == VDH_ACTION_IS_NOT_DONE) {

				GPT_StartTimer(TIM2,VDH_PROCESS_TIME_IN_ms);
				allFlags.combinedFlags.timer_10SecFlag = VDH_10SEC_ELAPSED;

				first_time = GPT_GetElapsedTime(TIM2);

				VDH_stateAllLeds(LED_OFF);

				LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_ON);


			}
			if (allFlags.combinedFlags.timer_10SecFlag == VDH_10SEC_ELAPSED){

				VDH_noActionState();

			}
		}
		else if(allFlags.combinedFlags.handle == VDH_HANDLE_IS_LOCKED && allFlags.combinedFlags.door == VDH_DOOR_IS_CLOSED){

			LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);

			LED_Activate(VDH_LEDS_PORT, VDH_LOCK_LED, LED_OFF);

			VDH_noActionState();

		}
	}

	return 0;
}




