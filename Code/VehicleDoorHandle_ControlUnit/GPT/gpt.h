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
#include "Rcc.h"


#define TIM2 ((TIMX_TYPE*)(TIM2_BASE_ADDRESS))
#define TIM3 ((TIMX_TYPE*)(TIM3_BASE_ADDRESS))
#define TIM4 ((TIMX_TYPE*)(TIM4_BASE_ADDRESS))
#define TIM5 ((TIMX_TYPE*)(TIM5_BASE_ADDRESS))


typedef enum{
	GPT_Elapsed, GPT_NotElapsed
}GPT_TimeIsElapsed;


void RCC_Timers_Intialization(void);

void GPT_Init(TIMX_TYPE* Timer ,TIMX_Mode_Selection Mode, CR1_CounterDirection Direction );

void GPT_StartTimer(TIMX_TYPE* Timer,uint32 OverFlowTicks);

GPT_TimeIsElapsed GPT_CheckTimeIsElapsed(TIMX_TYPE* Timer);

uint32 GPT_GetElapsedTime(TIMX_TYPE* Timer);

uint32 GPT_GetRemainingTime(TIMX_TYPE* Timer);

void Capture_Compare(TIMX_TYPE* Timer);

uint8 Capture_Compare_Flag(TIMX_TYPE* Timer);


#endif /* GPT_H_ */
