/*
 * GPT_Private.h
 *
 *  Created on: May 9, 2023
 *      Author: Anwar
 */

#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_

#include "Std_Types.h"

#define TIM2_BASE_ADDRESS 0x40000000

typedef struct{
	uint32 TIMx_CR1;
	uint32 TIMx_CR2;
	uint32 TIMx_SMCR;
	uint32 TIMx_DIER;
	uint32 TIMx_SR;
	uint32 TIMx_EGR;
	uint32 TIMx_CCMR1;
	uint32 TIMx_CCMR2;
	uint32 TIMx_CCER;
	uint32 TIMx_CNT;
	uint32 TIMx_PSC;
	uint32 TIMx_ARR;
	uint32 RESERVED_1;
	uint32 TIMx_CCR1;
	uint32 TIMx_CCR2;
	uint32 TIMx_CCR3;
	uint32 TIMx_CCR4;
	uint32 RESERVED_2;
	uint32 TIMx_DCR;
	uint32 TIMx_DMAR;
	uint32 TIM2_OR;
	uint32 TIM5_OR;
}TIM2_TYPE;




#endif /* GPT_PRIVATE_H_ */
