#include "stm32f10x.h"    // Device header
#include "PWM.h"

uint32_t i;

//static void NVIC_INIT(void)
//{	
//	//设置中断组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	//中断结构体
//	NVIC_InitTypeDef NVIC_Structure;
//	//中断通道
//	NVIC_Structure.NVIC_IRQChannel = TIM3_IRQn;
//	//通道使能
//	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;

//	//主优先级配置
//	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 0;
//	//抢占优先级
//	NVIC_Structure.NVIC_IRQChannelSubPriority = 3;
//	//NVIC初始化
//	NVIC_Init(&NVIC_Structure);
//}

//B0 B1
void U_TimerPWMInit(void) //高级定时器时基单元配置
{
		//初始化NVIC中断，配置中断优先级等。这里不需要使用中断
//	NVIC_INIT();
	
	/*！！！！时钟的使能要放在其余函数的前面，不然会有意想不到的结果！！！！*/
	//打开定时器的时钟，注意这里不要选错函数了（void RCC_APB1PeriphResetCmd(***)）
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//打开GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	//PWM输出口GPIO配置（这里使用的是输出比较通道3,4，对应的是GPIOB PIN0 GPIOB PIN1）
	GPIO_InitTypeDef GPIO_Structure;
	GPIO_Structure.GPIO_Mode = GPIO_Mode_AF_PP;//配置为复用输出模式，将GPIO的控制权交给片上外设而不是某某寄存器
	GPIO_Structure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//对应GPIOB的引脚
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Structure);
	
	//时基单元配置，使定时器的CNT计数器可以计数，用CNT的数与比较值进行比较，用来产生比较信号REF
	TIM_TimeBaseInitTypeDef BaseTimer_Structure;//定义时基结构体
	
	//时钟分频因子，这是用来“切割”系统时钟的。对应配置的是寄存器CR1的CKD[1:0](clock division)
	BaseTimer_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
		
	//计数模式，向上计数
	BaseTimer_Structure.TIM_CounterMode = TIM_CounterMode_Up;

	//重复寄存器数值，只有高级定时器才有不用管
//	BaseTimer_Structure.TIM_RepetitionCounter = 0;
	
	/*预分频器因子，用来驱动计数器CNT计数,这是用来“切割”来自APB1的时钟频率的，切割之后得到的频率用来
	驱动CNT计数*/
	BaseTimer_Structure.TIM_Prescaler = 0;//这里直接被切成72份，那么最后得到的频率为1M，这样CNT每1us记一次数
	
	/*定时器的计数周期，这个值会加载在寄存器ARR中，定时器工作时会将ARR的值与CNT计数
	器的值进行比较，如果值相等则产生更新中断等，更新中断也就是定时器被初始化或者计数
	器上溢或下溢。更新中断产生后对应SR寄存器的UIF（update interrupt flag）位将会被硬
	件置1（对于高级定时器则递减重复计数器的值），之后CNT又会重新计数*/
	BaseTimer_Structure.TIM_Period = 7200-1;//根据前面所说的，每1us记一次数，那么这里就代表从零开始计数
																				 //一直到100-1，一共计数100次，时间为0.1ms
	//基本定时器的时基初始化
	TIM_TimeBaseInit(TIM3,&BaseTimer_Structure);//初始化函数可以将结构体所有的参数写入对应的寄存器中
	
	/*将更新中断标志位清零,对应的是SR寄存器的UIF位清零，定时器
	产生更新中断后这一位由硬件自动置1，需要使用软件置0也就是复位。以下两个函数都可以使用，
//	这两个函数都是将SR寄存器的UIF位置0*/
//	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//TIM_ClearFlag(TIM6,TIM_IT_Update)
//	
//	//使能基本定时器的中断
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	//输出比较配置
	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);//将所有结构体成员进行一次初始化，这样更安全，也可以不写
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//使用PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//设置极性为高电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能输出比较
	//PWM比较值
	TIM_OCInitStructure.TIM_Pulse = 7200;//这个值就是前面所说的用来和CNT计数器的值比较的值（对应比较寄存器CCR），可以理解成高电平持续的时间
																		//根据不同模式，比较结果产生的功能不同
																		//这里使用的是PWM模式，比较结果就是用来改变输出的电平状态的。这里写的0，会一直输出低电平
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//初始化基于定时器3的输出捕获通道
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //这是预装载配置，可以写也可以不写
	
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);//使计数器CNT开始工作
}

