/*
�ļ���main.c
���ܣ���ʼ���������õ�����
PS��PID�����ڶ�ʱ��4�жϷ�������ÿ10ms��ȡһ��λ������Ȼ�����PID����
*/

#include "main.h"

int8_t Position;

int BaseLSpeed = 3900;//3600;
int BaseRSpeed = 3920;//3620;

void Beef(void);//������

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	

	USART_Config();
	LED3Configure();
	LED2Configure();
	LED1Configure();
	GENERAL_TIM_Init();
	OLED_Init();
	MotorInit();
	U_TimerPWMInit();
//PWM����
//	TIM_SetCompare3(TIM3,BaseRSpeed);//��
//	TIM_SetCompare4(TIM3,BaseLSpeed); 
		
	
	while (1)
	{ 		
		
	}
}

void RC_Control(uint8_t Dir)
{
	if(Dir == GoForward) Car_GoAlong();
	if(Dir == Turn_Left) Car_TurnLeft();
	if(Dir == Turn_Right) Car_TurnRight();
	if(Dir == Stop) Car_Stop();
	if(Dir == BigTurm) Car_BIG_Turn();
	
}

void IF_OpenTest(void)//����Ѱ��ģʽ��������
{
//	IF_Start();
	Position = IFPos_Read();
	if(Position == PosM) OLED_ShowString(1,3,"M ");
	else if (Position == PosR) OLED_ShowString(1,3,"R ");
	else if (Position == PosRR) OLED_ShowString(1,3,"RR");
	else if (Position == PosL) OLED_ShowString(1,3,"L ");
	else  OLED_ShowString(1,3,"LL");
	OLED_ShowString(1,6,"Erro:");
	OLED_ShowSignedNum(1,11,Pos,1);
}

void Beef(void)//������
{
	LED1_Change;
}




/*********************************************END OF FILE**********************/












