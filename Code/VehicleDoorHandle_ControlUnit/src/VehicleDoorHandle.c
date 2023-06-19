/*
 * VehicleDoorHandle.c
 *
 *  Created on: May 9, 2023
 *      Author: Anwar
 */
#include "VehicleDoorHandle.h"

extern uint32 first_time;

extern VDH_Flags allFlags;


void VDH_defaultState(void){
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	RCC_Timers_Intialization();

#ifdef EXTI_H_
	Rcc_Enable(RCC_SYSCFG);
#endif

	VDH_FlagInit();

	LED_Init(VDH_LEDS_PORT, VDH_LOCK_LED);
	LED_Activate(VDH_LEDS_PORT, VDH_LOCK_LED, LED_OFF);

	LED_Init(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED);
	LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_OFF);

	LED_Init(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED);
	LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);

	// Timer Testing Led
	LED_Init(VDH_LEDS_PORT, VDH_TEST_TIMERS_LED);

	BUTTON_Init(VDH_BUTTONS_PORT, VDH_HANDLE_LOCK_UNLOCK_BUTTON);
	BUTTON_Init(VDH_BUTTONS_PORT, VDH_DOOR_LOCK_UNLOCK_BUTTON);

	GPT_Init(TIM2 , Basic_Counter, Up_Counting);


#ifdef EXTI_H_
	Exti_Init(EXTI_GPIOB, VDH_DOOR_LOCK_UNLOCK_BUTTON, EXTI_FALLING_EDGE, VDH_doorButtonPressed);
#endif
}

void VDH_stateAllLeds(uint8 state){
	LED_Activate(VDH_LEDS_PORT, VDH_LOCK_LED, state);

	LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, state);

	LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, state);
}


void VDH_doorUnlock(void){

	static uint8 num_of_ticks = VDH_INIT_NUM_TICKS;
	uint32 time_elapsed = GPT_GetElapsedTime(TIM2);
	if ( (time_elapsed - first_time) >= VDH_HAZZARD_BLINKING_TIME) {
		num_of_ticks++;

		LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_OFF);

		if (num_of_ticks == (VDH_AMBIENT_HANDLE_UNLOCK_BLINKING_TIME/VDH_HAZZARD_BLINKING_TIME)) {
			LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);
			num_of_ticks = VDH_INIT_NUM_TICKS;
			allFlags.combinedFlags.doorUnlock_action = VDH_ACTION_IS_DONE;
		}
		first_time = GPT_GetElapsedTime(TIM2);
	}

}

void VDH_noActionState(void){


	static uint8 num_of_ticks = VDH_INIT_NUM_TICKS;

	uint32 time_elapsed = GPT_GetElapsedTime(TIM2);

	if( (time_elapsed - first_time) >= VDH_HAZZARD_BLINKING_TIME){
		num_of_ticks++;

		LED_Toggle(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED);

		first_time = GPT_GetElapsedTime(TIM2);

		if (num_of_ticks == ((VDH_HAZZARD_HANDLE_LOCK_BLINKING_TIME/VDH_HAZZARD_BLINKING_TIME)-1)) {
			num_of_ticks = VDH_INIT_NUM_TICKS;

			LED_Activate(VDH_LEDS_PORT, VDH_HAZARD_LIGHTS_LED, LED_OFF);
			allFlags.combinedFlags.handle = VDH_HANDLE_FLOATING_STATE;
			allFlags.combinedFlags.end_action = VDH_ACTION_IS_DONE;
			allFlags.combinedFlags.timer_10SecFlag = VDH_10SEC_NOT_ELAPSED;

			timerIsOn = BUTTON_TimerIsOff;
#ifdef EXTI_H_
			Exti_Disable(VDH_DOOR_LOCK_UNLOCK_BUTTON);
#endif
		}
	}

}

void VDH_doorIsClosed(void){
		uint32 time_elapsed = GPT_GetElapsedTime(TIM2);

		if( (time_elapsed - first_time) >= VDH_AMBIENT_CLOSED_DOOR_BLINKING_TIME){

			LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_OFF);

			GPT_StartTimer(TIM2,VDH_SECURITY_TIME_IN_ms);
			allFlags.combinedFlags.door_action = VDH_ACTION_IS_DONE;

			first_time = GPT_GetElapsedTime(TIM2);
		}
}

void VDH_doorButtonPressed(void){

	if (allFlags.combinedFlags.door == VDH_DOOR_IS_CLOSED) {
		allFlags.combinedFlags.door = VDH_DOOR_IS_OPENED;
	}
	else {
		allFlags.combinedFlags.door = VDH_DOOR_IS_CLOSED;
	}

	allFlags.combinedFlags.door_changeState = VDH_ACTION_IS_DONE;
	LED_Activate(VDH_LEDS_PORT, VDH_AMBIENT_LIGHT_LED, LED_ON);

	allFlags.combinedFlags.door_action = VDH_ACTION_IS_NOT_DONE;

	allFlags.combinedFlags.timer_10SecFlag = VDH_10SEC_NOT_ELAPSED;

	first_time = GPT_GetElapsedTime(TIM2);

#ifdef EXTI_H_
	Exti_HandlerPendingFlag(VDH_DOOR_LOCK_UNLOCK_BUTTON);
#endif
}


void VDH_FlagInit(void){
	allFlags.combinedFlags.door_action 		 = VDH_ACTION_IS_NOT_DONE;
	allFlags.combinedFlags.door_changeState  = VDH_ACTION_IS_NOT_DONE;
	allFlags.combinedFlags.end_action 		 = VDH_ACTION_IS_DONE;
	allFlags.combinedFlags.doorUnlock_action = VDH_ACTION_IS_NOT_DONE;
	allFlags.combinedFlags.handle 			 = VDH_HANDLE_FLOATING_STATE;
	allFlags.combinedFlags.door 			 = VDH_DOOR_IS_CLOSED;
	allFlags.combinedFlags.timer_10SecFlag 	 = VDH_10SEC_ELAPSED;
}



