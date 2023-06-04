#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/******define the PIN of LED******/
#define LED1_PIN GPIO_Pin_13
#define LED2_PIN GPIO_Pin_2
#define LED3_PIN GPIO_Pin_3
//#define LED4 GPIO_Pin_
//#define LED5 GPIO_Pin_
//#define LED6 GPIO_Pin_

/******define the PORT of LED******/
#define LED_PORT  GPIOC
#define LED1_PORT GPIOB
#define LED2_PORT GPIOC
#define LED3_PORT GPIOC
//#define LED4 GPIO_Pin_
//#define LED5 GPIO_Pin_
//#define LED6 GPIO_Pin_

/****define the RCC of AHB2 where LED is****/
#define LEDClock RCC_APB2Periph_GPIOC
#define LED1Clock RCC_APB2Periph_GPIOB
#define LED2Clock RCC_APB2Periph_GPIOC
#define LED3Clock RCC_APB2Periph_GPIOC
//#define LED4Clock GPIO_Pin
//#define LED5Clock GPIO_Pin
//#define LED6Clock GPIO_Pin

#define on 1
#define off 0
#define ON 1
#define OFF 0

#define Beef_Status(a)  if(a) \
													GPIO_ResetBits(LED1_PORT,LED1_PIN);

#define LED1_Status(a) if(a) \
													GPIO_ResetBits(LED1_PORT,LED1_PIN);\
											else GPIO_SetBits(LED1_PORT,LED1_PIN);
#define LED2_Status(a) if(a) \
													GPIO_ResetBits(LED_PORT,LED2_PIN);\
											else GPIO_SetBits(LED_PORT,LED2_PIN);
#define LED3_Status(a) if(a) \
													GPIO_ResetBits(LED_PORT,LED3_PIN);\
											else GPIO_SetBits(LED_PORT,LED3_PIN);

#define LED1_Change {GPIOB->ODR^=GPIO_Pin_13;}
#define LED2_Change {GPIOB->ODR^=GPIO_Pin_2;}
#define LED3_Change {GPIOB->ODR^=GPIO_Pin_3;}
#define Beef_Change {GPIOB->ODR^=GPIO_Pin_13;}

void LED1Configure(void);
void LED2Configure(void);
void LED3Configure(void);

#endif
