/*
 * ====================================================================================================================================
 *  Project		: Vehicle Door Handle Control Unit
 * 	File Name	: gpt.c
 *	Team 		: 20
 *	Members		: Abdelrahman Yasser - Omar Ahmed Anwar - Mo'men Mohamed - Neveen Mohamed
 *  ===================================================================================================================================
 */

/*---------------------- Includes ------------------------------------------*/
#include "gpt.h"
/*--------------------------------------------------------------------------*/

/*---------------------- Global Variables ----------------------------------*/
uint8 g_flag          = 0;

uint8 Counting_UpDown = 0;
/*--------------------------------------------------------------------------*/

/*---------------------- Functions Definition ------------------------------*/
void GPT_Init(TIMx_Configue* Timer){

	Timer->TIMx->TIMx_PSC = (Timer->prescaler)-1;

	if (Timer->direction == GPT_Down_Counting)
	{
		SET_BIT(Timer->TIMx->TIMx_CR1,CR1_DIR_BIT);
	}
	else if (Timer->direction == GPT_Up_Counting)
	{
		CLEAR_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}
	else if (Timer->direction == GPT_Up_Down_Counting)
	{
		SET_2_BITS(Timer->TIMx->TIMx_CR1,5);
	}

	SET_BIT(Timer->TIMx->TIMx_EGR, EGR_UG_BIT);

}


void GPT_StartTimer(TIMx_Configue* Timer,uint32 OverFlowTicks){

	Timer->TIMx->TIMx_ARR = OverFlowTicks;

	Timer->TIMx->TIMx_CNT = 0;

	g_flag = 1;

	SET_BIT(Timer->TIMx->TIMx_CR1, CR1_CEN_BIT);
}



GPT_TimeIsElapsed GPT_CheckTimeIsElapsed(TIMx_Configue* Timer){

	if (Timer->direction == GPT_Up_Down_Counting && g_flag){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}

	if( ( (Timer->direction == GPT_Down_Counting) || (Counting_UpDown == GPT_Down_Counting ) ) && g_flag)
	{
		if (Timer->TIMx->TIMx_CNT == 1)
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
		if (Timer->TIMx->TIMx_CNT == ((Timer->TIMx->TIMx_ARR)-1))
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




uint32 GPT_GetElapsedTime(TIMx_Configue* Timer){

	uint32 Counter = Timer->TIMx->TIMx_CNT;
	uint32 maxVal  = Timer->TIMx->TIMx_ARR;

	if (Timer->direction == GPT_Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}

	if ((Timer->direction == GPT_Down_Counting) || (Counting_UpDown == GPT_Down_Counting))
	{
		Counter = maxVal - Counter ;
	}
	return Counter;
}




uint32 GPT_GetRemainingTime(TIMx_Configue* Timer){

	uint32 remainingTime;
	if (Timer->direction == GPT_Up_Down_Counting ){
		Counting_UpDown= READ_BIT(Timer->TIMx->TIMx_CR1, CR1_DIR_BIT);
	}
	if( (Timer->direction == GPT_Down_Counting) ||(Counting_UpDown == GPT_Down_Counting) )
	{
		remainingTime = Timer->TIMx->TIMx_CNT;
	}
	else
	{
		remainingTime= (Timer->TIMx->TIMx_ARR - Timer->TIMx->TIMx_CNT);

	}

	return remainingTime;
}
/*--------------------------------------------------------------------------*/



