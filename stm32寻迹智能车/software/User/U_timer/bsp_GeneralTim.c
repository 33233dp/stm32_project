/*
*�ļ���bsp_GeneralTim.c
*���������ļ�ֻ�����˶�ʱ��4�Ļ������ܣ��������˼�ʱ�͸����жϡ���ʱ��������Ϊ��10ms
*���ڣ�2022.10.10
*���ã���ʱ��4���жϷ��������ڶ�ȡ����Ѱ��ģ�����ɼ���С��ͷ��λ����Ϣ����λ����Ϣͨ��PID���㴦��������һ��PWM��ֵ
*      �ò����ṩ����ʱ3�������PWM�������ļ�PWM.c��
*/

#include "bsp_GeneralTim.h"
#include "main.h"



// �ж����ȼ�����
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



static void GENERAL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;
	  // ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;	
		// ʱ�ӷ�Ƶ���� ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
		// ����������жϱ�־λ
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Mode_Config();
}

/*
float Q,Act,OutPut;
float Kp, Ki, Kd,Erro,ErroI, ErroLast;
float a[100];
*/

typedef struct//PID��ز���
{
	int ActPos;//ʵ��λ��
	int AmyPos;//Ŀ��λ��
	int PwmOut;//Pwm���ֵ
	int Kp;//PID����
	int Ki;
	int Kd;
	int Erro;//��ǰ���
	int LastErro;//��һ�����
	int ErroI;//�ۻ����
}PidStructuretypedef;

PidStructuretypedef PIDStructure;

int PID_PWM(int ActPos)
{
	//��ֵ
	PIDStructure.AmyPos = 0;
	PIDStructure.ActPos = ActPos;
	PIDStructure.Kp = 400;
	PIDStructure.Ki = 0;
	PIDStructure.Kd = 2400;
	
	//����
	PIDStructure.Erro = PIDStructure.AmyPos - PIDStructure.ActPos;//���
	PIDStructure.ErroI += PIDStructure.Erro;
	PIDStructure.PwmOut = PIDStructure.Kp * PIDStructure.Erro + PIDStructure.Ki *	PIDStructure.ErroI + PIDStructure.Kd *(PIDStructure.Erro - PIDStructure.LastErro);
	PIDStructure.LastErro = PIDStructure.Erro;
	
	//����PWM
	return PIDStructure.PwmOut;
}


int OUTPwm;//PID���������PWM
int OUTPUT_L ;//�������
int OUTPUT_R ; 

void LimitPwm(void);//�޷�����


void  GENERAL_TIM_IRQHandler (void)//��ʱ���жϷ�����
{
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		IFPos_Read();
		OLED_ShowSignedNum(2,1,Pos,3);
		OLED_ShowSignedNum(3,1,Erro,2);
		OUTPwm = PID_PWM(Erro);//PID����
		LimitPwm();//����PWM��ֵ������7200

		//���PWM
		TIM_SetCompare3(TIM3,OUTPUT_R);//��
		TIM_SetCompare4(TIM3,OUTPUT_L);
	}	
	TIM_ClearITPendingBit(GENERAL_TIM , TIM_FLAG_Update); 	 	
}

void LimitPwm(void)//�޷�����
{
	OUTPUT_L = BaseLSpeed - OUTPwm;
	OUTPUT_R = BaseRSpeed + OUTPwm;

	if(OUTPUT_L > 7200)	OUTPUT_L = 7200;
	if(OUTPUT_L < 0 ) OUTPUT_L = 0;
	if(OUTPUT_R > 7200)	OUTPUT_R = 7200;
	if(OUTPUT_R < 0 ) OUTPUT_R = 0;
}
