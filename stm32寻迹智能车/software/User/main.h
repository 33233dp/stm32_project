#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "LED.h"
#include "OLED.h"
#include "bsp_AdvanceTim_PWM_SG90.h"
#include "Key.h"
#include "IF_Tracing.h"
#include "Motor.h"
#include "bsp_GeneralTim.h"
#include "PWM.h"
#include "Delay.h"


#define Turn_Right 3
#define Turn_Left 2
#define GoForward 1
#define Stop 0
#define BigTurm 4
#define Mid IF3_Flag
#define Right IF2_Flag
#define Left IF1_Flag

extern uint8_t KeyNum;
extern int BaseLSpeed ;
extern int BaseRSpeed ;


void RC_Control(uint8_t Dir);
void IF_Tracing(void);
void IF_OpenTest(void);//红外寻迹模式开机测试
void Beef(void);//蜂鸣器

#endif
