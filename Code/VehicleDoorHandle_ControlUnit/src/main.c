/*
 * main.c
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */

#include "VehicleDoorHandle.h"

extern Action_State door_action;

Action_State end_action = VDH_ACTION_IS_DONE;

Action_State doorUnlock_action = VDH_ACTION_IS_NOT_DONE;

Handle_State handle = VDH_HANDLE_FLOATING_STATE;

Door_State door = VDH_DOOR_FLOATING_STATE;

Time_State timer_10SecFlag = VDH_10SEC_ELAPSED;

uint32 first_time = 0;

int main(void) {
	VDH_defaultState();

	while(1){


		if (BUTTON_ReadState(VDH_BUTTONS_PORT, VDH_HANDLE_LOCK_UNLOCK_BUTTON) == BUTTON_PRESSED) {

			if(handle == VDH_HANDLE_FLOATING_STATE){
				handle = VDH_HANDLE_IS_LOCKED;
			}

			if (handle == VDH_HANDLE_IS_LOCKED) {
				handle = VDH_HANDLE_IS_UNLOCKED;
			}
			else {
				handle = VDH_HANDLE_IS_LOCKED;
			}
			end_action = VDH_ACTION_IS_NOT_DONE;

			timer_10SecFlag = VDH_10SEC_NOT_ELAPSED;

			doorUnlock_action = VDH_ACTION_IS_NOT_DONE;

			VDH_stateAllLeds(LED_ON);
			GPT_StartTimer(VDH_SECURITY_TIME_IN_ms);
			first_time = GPT_GetElapsedTime();
		}


		if (handle == VDH_HANDLE_IS_UNLOCKED) {
			if (doorUnlock_action == VDH_ACTION_IS_NOT_DONE) {
				VDH_doorUnlock();
			}
			if (BUTTON_ReadState(VDH_BUTTONS_PORT, VDH_DOOR_LOCK_UNLOCK_BUTTON) == BUTTON_PRESSED) {

				if(door == VDH_DOOR_FLOATING_STATE){
					door = VDH_DOOR_IS_CLOSED;
				}

				if (door == VDH_DOOR_IS_CLOSED) {
					door = VDH_DOOR_IS_OPENED;
				}
				else {
					door = VDH_DOOR_IS_CLOSED;
				}
				LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_ON);

				door_action = VDH_ACTION_IS_NOT_DONE;

				timer_10SecFlag = VDH_10SEC_NOT_ELAPSED;

				first_time = GPT_GetElapsedTime();
			}
			if ((door == VDH_DOOR_IS_CLOSED) && (door_action == VDH_ACTION_IS_NOT_DONE)) {

				VDH_doorIsClosed();

			}
			if (GPT_GetElapsedTime() == GPT_Elapsed && timer_10SecFlag == VDH_10SEC_NOT_ELAPSED && (door == VDH_DOOR_IS_CLOSED || door == VDH_DOOR_FLOATING_STATE)) {

				timer_10SecFlag = VDH_10SEC_ELAPSED;

				first_time = GPT_GetElapsedTime();

				VDH_stateAllLeds(LED_OFF);

				LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_ON);

			}
			if (timer_10SecFlag == VDH_10SEC_ELAPSED){

				VDH_noActionState();

			}
		}
		else if(handle == VDH_HANDLE_IS_LOCKED){

			LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);

			LED_Activate(VDH_LEDS_PORT, VDH_LOCK_LED, LED_OFF);

			VDH_noActionState();

		}
	}

	return 0;
}




