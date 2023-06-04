#include "LED.h"

void LED1Configure(void)
{
	GPIO_InitTypeDef LED_Structure;
	LED_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_Structure.GPIO_Pin  = LED1_PIN;
	LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(LED1Clock,ENABLE);
	GPIO_Init(LED1_PORT,&LED_Structure);
	GPIO_SetBits(LED1_PORT,LED1_PIN);


}

void LED2Configure(void)
{
	GPIO_InitTypeDef LED_Structure;
	LED_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_Structure.GPIO_Pin  = LED2_PIN;
	LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(LEDClock,ENABLE);
	GPIO_Init(LED_PORT,&LED_Structure);
	GPIO_SetBits(LED_PORT,LED2_PIN);

}

void LED3Configure(void)
{
	GPIO_InitTypeDef LED_Structure;
	LED_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_Structure.GPIO_Pin  = LED3_PIN;
	LED_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(LEDClock,ENABLE);
	GPIO_Init(LED_PORT,&LED_Structure);
	GPIO_SetBits(LED_PORT,LED3_PIN);
}
