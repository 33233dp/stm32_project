#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H

#include "stm32f10x.h"

/****¶¨Ê±Æ÷4****/
#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_PERIOD            10000-1
#define            GENERAL_TIM_PSC              (72-1)


#define            GENERAL_TIM_IRQ               TIM4_IRQn
#define            GENERAL_TIM_IRQHandler           TIM4_IRQHandler 
/**************/


void GENERAL_TIM_Init(void);


#endif	/* __BSP_GENERALTIME_H */
