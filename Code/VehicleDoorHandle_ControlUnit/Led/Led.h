/*
 * Led.h
 *
 *  Created on: May 8, 2023
 *      Author: Anwar
 */

#ifndef LED_H_
#define LED_H_

#define LED_ON		1
#define LED_OFF		0

#include "Gpio.h"

void LED_Init(uint8 portName, uint8 pinNum);

void LED_Activate(uint8 portName, uint8 pinNum, uint8 state);

void LED_Toggle(uint8 portName, uint8 pinNum);

#endif /* LED_H_ */
