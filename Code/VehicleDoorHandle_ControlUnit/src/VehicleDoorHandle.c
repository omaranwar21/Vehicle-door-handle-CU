/*
 * VehicleDoorHandle.c
 *
 *  Created on: May 9, 2023
 *      Author: Anwar
 */
#include "VehicleDoorHandle.h"

extern boolean handle;
Action_State door_action = VDH_ACTION_IS_NOT_DONE;
extern Action_State end_action;
extern boolean timer_10SecFlag;
extern uint32 first_time;
extern Action_State doorUnlock_action;

void VDH_defaultState(void){
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	Rcc_Enable(RCC_TIM2);

	LED_Init(VDH_LEDS_PORT, VDH_LOCK_LED);
	LED_Activate(VDH_LEDS_PORT, VDH_LOCK_LED, LED_OFF);

	LED_Init(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED);
	LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_OFF);

	LED_Init(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED);
	LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);

	BUTTON_Init(VDH_BUTTONS_PORT, VDH_HANDLE_LOCK_UNLOCK_BUTTON);
	BUTTON_Init(VDH_BUTTONS_PORT, VDH_DOOR_LOCK_UNLOCK_BUTTON);

	GPT_Init();
}

void VDH_stateAllLeds(uint8 state){
	LED_Activate(VDH_LEDS_PORT, VDH_LOCK_LED, state);

	LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, state);

	LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, state);
}


void VDH_doorUnlock(void){

	static uint8 num_of_ticks = VDH_INIT_NUM_TICKS;
	uint32 time_elapsed = GPT_GetElapsedTime();
	if ( (time_elapsed - first_time) >= VDH_HAZZARD_BLINKING_TIME) {
		num_of_ticks++;

		LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_OFF);

		if (num_of_ticks == (VDH_AMBIENT_HANDLE_UNLOCK_BLINKING_TIME/VDH_HAZZARD_BLINKING_TIME)) {
			LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);
			num_of_ticks = VDH_INIT_NUM_TICKS;
			doorUnlock_action = VDH_ACTION_IS_DONE;
		}
		first_time = GPT_GetElapsedTime();
	}

}

void VDH_noActionState(void){


	static uint8 num_of_ticks = VDH_INIT_NUM_TICKS;

	uint32 time_elapsed = GPT_GetElapsedTime();

	if( (time_elapsed - first_time) >= VDH_HAZZARD_BLINKING_TIME){
		num_of_ticks++;

		LED_Toggle(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED);

		first_time = GPT_GetElapsedTime();

		if (num_of_ticks == ((VDH_HAZZARD_HANDLE_LOCK_BLINKING_TIME/VDH_HAZZARD_BLINKING_TIME)-1)) {
			num_of_ticks = VDH_INIT_NUM_TICKS;

			LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_OFF);
			handle = VDH_HANDLE_FLOATING_STATE;
			end_action = VDH_ACTION_IS_DONE;
			timer_10SecFlag = VDH_10SEC_NOT_ELAPSED;
		}
	}

}

void VDH_doorIsClosed(void){
		uint32 time_elapsed = GPT_GetElapsedTime();

		if( (time_elapsed - first_time) >= VDH_AMBIENT_CLOSED_DOOR_BLINKING_TIME){

			LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);

			GPT_StartTimer(VDH_SECURITY_TIME_IN_ms);
			door_action = VDH_ACTION_IS_DONE;

			first_time = GPT_GetElapsedTime();
		}
}



