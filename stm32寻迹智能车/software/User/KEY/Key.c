#include "stm32f10x.h"                  // Device header
#include "Delay.h"

 unsigned int Num;

void GPIO_UPInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructureB;
	GPIO_InitStructureB.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructureB.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructureB.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructureB);
	GPIO_Init(GPIOB,&GPIO_InitStructureB);
}

unsigned char Key(void)
{
	
	GPIO_UPInit();
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0) {Num=1;}
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0) {Num=2;}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) == 0) 
	{
		Delay_ms(15);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) == 0);
		Delay_ms(15);
		return 1;
	}
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) == 0) 
	{
		Delay_ms(15);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) == 0);
		Delay_ms(15);
		return 2;
	}
//	
	else return Num = 0;

}
