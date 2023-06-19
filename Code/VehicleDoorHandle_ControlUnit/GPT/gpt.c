/*
 * gpt.c
 *
 *  Created on: May 9, 2023
 *      Author: Anwar
 */

#include "gpt.h"

uint8 g_flag          = 0;
uint8 Counting_Down   = 0;
uint8 Counting_UpDown = 0;
uint8 TIMX_MODE       = 0;



void RCC_Timers_Intialization(void)
{
	Rcc_Enable(RCC_TIM2);
	Rcc_Enable(RCC_TIM3);
//	Rcc_Enable(RCC_TIM4);
//	Rcc_Enable(RCC_TIM5);
//	Rcc_Enable(RCC_TIM9);
//	Rcc_Enable(RCC_TIM10);
//	Rcc_Enable(RCC_TIM11);

}



void GPT_Init(TIMX_TYPE* Timer ,TIMX_Mode_Selection Mode, CR1_CounterDirection Direction ){

	Timer->TIMx_PSC = 4000-1;

	if (Direction == Down_Counting)
	{
		Counting_Down = Down_Counting;
		SET_BIT(Timer->TIMx_CR1,CR1_DIR_BIT);
	}
	else if (Direction == Up_Counting)
	{
		CLEAR_BIT(Timer->TIMx_CR1, CR1_DIR_BIT);
	}
	else if (Direction == Up_Down_Counting)
	{
		Counting_UpDown = Up_Down_Counting;
		SET_2_BITS(Timer->TIMx_CR1,5);
	}

	//		SET_BIT(Timer->TIMx_DIER,DIER_UIE_BIT);  // we should clear it with TIMX_IQR_Callback to can be set again with every event(read at UIF BIT IN SR)


}


void GPT_StartTimer(TIMX_TYPE* Timer,uint32 OverFlowTicks){
	CLEAR_BIT(Timer->TIMx_CR1, CR1_CEN_BIT);

	Timer->TIMx_ARR = OverFlowTicks;
		Timer->TIMx_CNT = 1;
//	Timer->TIMx_CNT = 0;
	g_flag = 1;
	SET_BIT(Timer->TIMx_CR1, CR1_CEN_BIT);
}



GPT_TimeIsElapsed GPT_CheckTimeIsElapsed(TIMX_TYPE* Timer){

	if (Counting_UpDown == Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx_CR1, CR1_DIR_BIT);
	}

	if((Counting_Down == Down_Counting) || (Counting_UpDown == Down_Counting ))
	{
		if (Timer->TIMx_CNT == 1 && g_flag)
		{
			g_flag = 0;
			return GPT_Elapsed;
		}
		else
		{
			return GPT_NotElapsed;
		}

	}
	else
	{
		if (Timer->TIMx_CNT == ((Timer->TIMx_ARR)-1) && g_flag)
		{
			g_flag = 0;
			return GPT_Elapsed;
		}
		else
		{
			return GPT_NotElapsed;
		}
	}
}




uint32 GPT_GetElapsedTime(TIMX_TYPE* Timer){

	uint32 Counter = Timer->TIMx_CNT;
	uint32 maxVal  = Timer->TIMx_ARR;

	if (Counting_UpDown == Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx_CR1, CR1_DIR_BIT);
	}

	if ((Counting_Down == Down_Counting) || (Counting_UpDown == Down_Counting))
	{
		Counter = maxVal - Counter ;
	}
	return Counter;
}




uint32 GPT_GetRemainingTime(TIMX_TYPE* Timer){

	uint32 remainingTime;
	if (Counting_UpDown == Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx_CR1, CR1_DIR_BIT);
	}
	if( (Counting_Down == Down_Counting) ||(Counting_UpDown == Down_Counting) )
	{
		remainingTime = Timer->TIMx_CNT;
	}
	else
	{
		remainingTime= (Timer->TIMx_ARR - Timer->TIMx_CNT);

	}

	return remainingTime;
}

//,TIMX_Mode_Selection Mode

void Capture_Compare(TIMX_TYPE* Timer)
{
	CLEAR_2_BITS(Timer->TIMx_CCMR1,0); // put 00 at Bits( 0,1) for output compare mode
	Timer->TIMx_CCMR1 &= ~(0b11); // Clear bits 0 and 1 (output compare mode)
	Timer->TIMx_CCMR1|= (1<<4);        // 001: Set channel 1 to active level on match
	//		Timer->TIMx_CCMR1|= (2<<4);// 010: Set channel 1 to inactive level on match.
	Timer->TIMx_CCR1 = 100;
	SET_BIT(Timer->TIMx_CCER,0);       // Enable capture/compare channel 1 output
}

uint8 Capture_Compare_Flag(TIMX_TYPE* Timer)
{
	uint8 Flag = READ_BIT(Timer->TIMx_SR, 1);

	return Flag;
}


