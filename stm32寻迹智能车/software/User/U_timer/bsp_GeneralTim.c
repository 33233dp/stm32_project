/*
*文件：bsp_GeneralTim.c
*描述：此文件只配置了定时器4的基础功能，即允许了计时和更新中断。定时周期设置为了10ms
*日期：2022.10.10
*作用：定时器4的中断服务函数用于读取红外寻迹模块所采集的小车头的位置信息，将位置信息通过PID运算处理过后输出一个PWM数值
*      该参数提供给定时3用于输出PWM波（见文件PWM.c）
*/

#include "bsp_GeneralTim.h"
#include "main.h"



// 中断优先级配置
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



static void GENERAL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;
	  // 时钟预分频数
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;	
		// 时钟分频因子 ，没用到不用管
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		// 重复计数器的值，没用到不用管
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	  // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
		// 清除计数器中断标志位
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
		
		// 使能计数器
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

typedef struct//PID相关参数
{
	int ActPos;//实际位置
	int AmyPos;//目标位置
	int PwmOut;//Pwm输出值
	int Kp;//PID参数
	int Ki;
	int Kd;
	int Erro;//当前误差
	int LastErro;//上一次误差
	int ErroI;//累积误差
}PidStructuretypedef;

PidStructuretypedef PIDStructure;

int PID_PWM(int ActPos)
{
	//赋值
	PIDStructure.AmyPos = 0;
	PIDStructure.ActPos = ActPos;
	PIDStructure.Kp = 400;
	PIDStructure.Ki = 0;
	PIDStructure.Kd = 2400;
	
	//运算
	PIDStructure.Erro = PIDStructure.AmyPos - PIDStructure.ActPos;//误差
	PIDStructure.ErroI += PIDStructure.Erro;
	PIDStructure.PwmOut = PIDStructure.Kp * PIDStructure.Erro + PIDStructure.Ki *	PIDStructure.ErroI + PIDStructure.Kd *(PIDStructure.Erro - PIDStructure.LastErro);
	PIDStructure.LastErro = PIDStructure.Erro;
	
	//返回PWM
	return PIDStructure.PwmOut;
}


int OUTPwm;//PID运算输出的PWM
int OUTPUT_L ;//左轮输出
int OUTPUT_R ; 

void LimitPwm(void);//限幅函数


void  GENERAL_TIM_IRQHandler (void)//定时器中断服务函数
{
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		IFPos_Read();
		OLED_ShowSignedNum(2,1,Pos,3);
		OLED_ShowSignedNum(3,1,Erro,2);
		OUTPwm = PID_PWM(Erro);//PID运算
		LimitPwm();//限制PWM的值不大于7200

		//输出PWM
		TIM_SetCompare3(TIM3,OUTPUT_R);//右
		TIM_SetCompare4(TIM3,OUTPUT_L);
	}	
	TIM_ClearITPendingBit(GENERAL_TIM , TIM_FLAG_Update); 	 	
}

void LimitPwm(void)//限幅函数
{
	OUTPUT_L = BaseLSpeed - OUTPwm;
	OUTPUT_R = BaseRSpeed + OUTPwm;

	if(OUTPUT_L > 7200)	OUTPUT_L = 7200;
	if(OUTPUT_L < 0 ) OUTPUT_L = 0;
	if(OUTPUT_R > 7200)	OUTPUT_R = 7200;
	if(OUTPUT_R < 0 ) OUTPUT_R = 0;
}
