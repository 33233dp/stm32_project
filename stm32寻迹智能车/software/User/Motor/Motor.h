#ifndef __Motor_H__
#define __Motor_H__

#include "stm32f10x.h"                  // Device header


/****电机引脚定义****/
/*B0C4 B1C7*/
//MOTOR1 B0C4
#define Motor1_PinA GPIO_Pin_0
#define Motor1_PinB GPIO_Pin_4
#define Motor1_PORTA GPIOB
#define Motor1_PORTB GPIOC
//MOTOR2 B1C7
#define Motor2_PinA GPIO_Pin_1
#define Motor2_PinB GPIO_Pin_7
#define Motor2_PORTA GPIOB
#define Motor2_PORTB GPIOC

/**/

/**电机使能引脚**/
/***C11 C12***/
#define EN1_Pin GPIO_Pin_11 //Motor1
#define EN2_Pin GPIO_Pin_12 //Motor2

#define EN1_PORT GPIOC
#define EN2_PORT GPIOC

/****电机引脚时钟定义****/
#define RCC_Motor1 RCC_APB2Periph_GPIOB
#define RCC_Motor2 RCC_APB2Periph_GPIOC

/****电机使能引脚时钟****/
#define RCC_EN1 RCC_APB2Periph_GPIOC
#define RCC_EN2 RCC_APB2Periph_GPIOC


extern uint32_t PWMA,PWMB,Time;

/*遥控模式*/
void MotorGPIO_Init(void);
void MotorInit(void);
void Car_TurnLeft(void);
void Car_TurnRight(void);
void Car_GoAlong(void);
void Car_Stop(void);
void Car_BIG_Turn(void);

/*红外寻迹模式*/
void RightRotation(void);
void LeftRotation(void);
void NoRotation(void);

#endif
