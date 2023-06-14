/*
 * gpt.h
 *
 *  Created on: May 9, 2023
 *      Author: Anwar
 */

#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"
#include "GPT_Private.h"
#include "Bit_Operations.h"

#define TIM2 ((TIM2_TYPE*)(TIM2_BASE_ADDRESS))

typedef enum{
	GPT_Elapsed, GPT_NotElapsed
}GPT_TimeIsElapsed;

void GPT_Init(void);
void GPT_StartTimer(uint32 OverFlowTicks);
GPT_TimeIsElapsed GPT_CheckTimeIsElapsed(void);
uint32 GPT_GetElapsedTime(void);
uint32 GPT_GetRemainingTime(void);


#endif /* GPT_H_ */
