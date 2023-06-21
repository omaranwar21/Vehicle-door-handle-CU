/*
 * VehicleDoorHandle.h
 *
 *  Created on: May 9, 2023
 *      Author: Anwar
 */

#ifndef VEHICLEDOORHANDLE_H_
#define VEHICLEDOORHANDLE_H_

#include "Led.h"
#include "Button.h"
#include "Rcc.h"
#include "gpt.h"

#define VDH_BUTTONS_PORT							GPIO_B
#define VDH_HANDLE_LOCK_UNLOCK_BUTTON				5
#define VDH_DOOR_LOCK_UNLOCK_BUTTON					8

#define VDH_LEDS_PORT								GPIO_A
#define VDH_LOCK_LED								2
#define VDH_HAZARD_LIGHTS_LED						4
#define VDH_AMBIENT_LIGHT_LED						6

#define VDH_SECURITY_TIME_IN_ms						10000
#define VDH_HAZZARD_BLINKING_TIME					500
#define VDH_AMBIENT_CLOSED_DOOR_BLINKING_TIME		1000
#define VDH_AMBIENT_HANDLE_UNLOCK_BLINKING_TIME		2000
#define VDH_HAZZARD_HANDLE_LOCK_BLINKING_TIME		2000

#define VDH_INIT_NUM_TICKS							0

typedef enum{
	VDH_DOOR_IS_CLOSED, VDH_DOOR_IS_OPENED, VDH_DOOR_FLOATING_STATE
}Door_State;

typedef enum{
	VDH_HANDLE_IS_LOCKED, VDH_HANDLE_IS_UNLOCKED, VDH_HANDLE_FLOATING_STATE
}Handle_State;

typedef enum{
	VDH_10SEC_NOT_ELAPSED, VDH_10SEC_ELAPSED
}Time_State;

typedef enum{
	VDH_ACTION_IS_NOT_DONE, VDH_ACTION_IS_DONE
}Action_State;

void VDH_stateAllLeds(uint8);
void VDH_defaultState(void);
void VDH_doorUnlock(void);
void VDH_noActionState(void);
void VDH_doorIsClosed(void);


#endif /* VEHICLEDOORHANDLE_H_ */
