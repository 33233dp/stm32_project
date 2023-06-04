/*
电机驱动板使能等引脚配置
*/

#include "main.h"
#include "Motor.h"

uint32_t Time;
uint32_t  PWMA;
uint32_t  PWMB;

static void MotorGPIO_Init(void)
{
	/****Motor1****/
	GPIO_InitTypeDef Motor1_Structure;
	Motor1_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	Motor1_Structure.GPIO_Pin  = Motor1_PinA|Motor1_PinB;
	Motor1_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_Motor1,ENABLE);
	GPIO_Init(Motor1_PORTA,&Motor1_Structure);
	GPIO_Init(Motor1_PORTB,&Motor1_Structure);

	/****Motor2****/
	GPIO_InitTypeDef Motor2_Structure;
	Motor2_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	Motor2_Structure.GPIO_Pin  = Motor2_PinA|Motor2_PinB;
	Motor2_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_Motor2,ENABLE);
	GPIO_Init(Motor2_PORTA,&Motor2_Structure);
	GPIO_Init(Motor2_PORTB,&Motor2_Structure);
	
	/*------EN1 EN2------*/
	GPIO_InitTypeDef EN_Structure;
	EN_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	EN_Structure.GPIO_Pin  = EN1_Pin|EN2_Pin;
	EN_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_EN1,ENABLE);
	GPIO_Init(EN1_PORT,&EN_Structure);
	GPIO_Init(EN2_PORT,&EN_Structure);
	
}

void MotorInit(void)
{
	MotorGPIO_Init();
	GPIO_SetBits(Motor1_PORTA,Motor1_PinA);
	GPIO_SetBits(Motor1_PORTB,Motor1_PinB);
	GPIO_SetBits(Motor2_PORTA,Motor2_PinA);
	GPIO_SetBits(Motor2_PORTB,Motor2_PinB);
	GPIO_SetBits(EN1_PORT,EN1_Pin);
	GPIO_SetBits(EN2_PORT,EN2_Pin);
}





void Car_IF(void)
{
	
}




/*遥控模式方向*/
void Car_TurnLeft(void)
{
	PWMA = 20;
	PWMB = 50;
}

void Car_TurnRight(void)
{
	PWMA = 50;
	PWMB = 20;
}

void Car_BIG_Turn(void)
{
	PWMA = 75;
	PWMB = 40;
}

void Car_GoAlong(void)
{
	PWMA = 61;
	PWMB = 60;
}

/*
void Car_GoBack(void)
{
	PWMA = 50;
	PWMB = 50;
}*/
void Car_Stop(void)
{
	PWMA = 0;
	PWMB = 0;
}



