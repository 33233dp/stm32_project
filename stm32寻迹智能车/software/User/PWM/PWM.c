#include "stm32f10x.h"    // Device header
#include "PWM.h"

uint32_t i;

//static void NVIC_INIT(void)
//{	
//	//�����ж���
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	//�жϽṹ��
//	NVIC_InitTypeDef NVIC_Structure;
//	//�ж�ͨ��
//	NVIC_Structure.NVIC_IRQChannel = TIM3_IRQn;
//	//ͨ��ʹ��
//	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;

//	//�����ȼ�����
//	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 0;
//	//��ռ���ȼ�
//	NVIC_Structure.NVIC_IRQChannelSubPriority = 3;
//	//NVIC��ʼ��
//	NVIC_Init(&NVIC_Structure);
//}

//B0 B1
void U_TimerPWMInit(void) //�߼���ʱ��ʱ����Ԫ����
{
		//��ʼ��NVIC�жϣ������ж����ȼ��ȡ����ﲻ��Ҫʹ���ж�
//	NVIC_INIT();
	
	/*��������ʱ�ӵ�ʹ��Ҫ�������ຯ����ǰ�棬��Ȼ�������벻���Ľ����������*/
	//�򿪶�ʱ����ʱ�ӣ�ע�����ﲻҪѡ�����ˣ�void RCC_APB1PeriphResetCmd(***)��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//��GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	//PWM�����GPIO���ã�����ʹ�õ�������Ƚ�ͨ��3,4����Ӧ����GPIOB PIN0 GPIOB PIN1��
	GPIO_InitTypeDef GPIO_Structure;
	GPIO_Structure.GPIO_Mode = GPIO_Mode_AF_PP;//����Ϊ�������ģʽ����GPIO�Ŀ���Ȩ����Ƭ�����������ĳĳ�Ĵ���
	GPIO_Structure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//��ӦGPIOB������
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Structure);
	
	//ʱ����Ԫ���ã�ʹ��ʱ����CNT���������Լ�������CNT������Ƚ�ֵ���бȽϣ����������Ƚ��ź�REF
	TIM_TimeBaseInitTypeDef BaseTimer_Structure;//����ʱ���ṹ��
	
	//ʱ�ӷ�Ƶ���ӣ������������иϵͳʱ�ӵġ���Ӧ���õ��ǼĴ���CR1��CKD[1:0](clock division)
	BaseTimer_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
		
	//����ģʽ�����ϼ���
	BaseTimer_Structure.TIM_CounterMode = TIM_CounterMode_Up;

	//�ظ��Ĵ�����ֵ��ֻ�и߼���ʱ�����в��ù�
//	BaseTimer_Structure.TIM_RepetitionCounter = 0;
	
	/*Ԥ��Ƶ�����ӣ���������������CNT����,�����������и����APB1��ʱ��Ƶ�ʵģ��и�֮��õ���Ƶ������
	����CNT����*/
	BaseTimer_Structure.TIM_Prescaler = 0;//����ֱ�ӱ��г�72�ݣ���ô���õ���Ƶ��Ϊ1M������CNTÿ1us��һ����
	
	/*��ʱ���ļ������ڣ����ֵ������ڼĴ���ARR�У���ʱ������ʱ�ὫARR��ֵ��CNT����
	����ֵ���бȽϣ����ֵ�������������жϵȣ������ж�Ҳ���Ƕ�ʱ������ʼ�����߼���
	����������硣�����жϲ������ӦSR�Ĵ�����UIF��update interrupt flag��λ���ᱻӲ
	����1�����ڸ߼���ʱ����ݼ��ظ���������ֵ����֮��CNT�ֻ����¼���*/
	BaseTimer_Structure.TIM_Period = 7200-1;//����ǰ����˵�ģ�ÿ1us��һ��������ô����ʹ�����㿪ʼ����
																				 //һֱ��100-1��һ������100�Σ�ʱ��Ϊ0.1ms
	//������ʱ����ʱ����ʼ��
	TIM_TimeBaseInit(TIM3,&BaseTimer_Structure);//��ʼ���������Խ��ṹ�����еĲ���д���Ӧ�ļĴ�����
	
	/*�������жϱ�־λ����,��Ӧ����SR�Ĵ�����UIFλ���㣬��ʱ��
	���������жϺ���һλ��Ӳ���Զ���1����Ҫʹ�������0Ҳ���Ǹ�λ��������������������ʹ�ã�
//	�������������ǽ�SR�Ĵ�����UIFλ��0*/
//	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//TIM_ClearFlag(TIM6,TIM_IT_Update)
//	
//	//ʹ�ܻ�����ʱ�����ж�
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	//����Ƚ�����
	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);//�����нṹ���Ա����һ�γ�ʼ������������ȫ��Ҳ���Բ�д
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ʹ��PWMģʽ1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//���ü���Ϊ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�
	//PWM�Ƚ�ֵ
	TIM_OCInitStructure.TIM_Pulse = 7200;//���ֵ����ǰ����˵��������CNT��������ֵ�Ƚϵ�ֵ����Ӧ�ȽϼĴ���CCR�����������ɸߵ�ƽ������ʱ��
																		//���ݲ�ͬģʽ���ȽϽ�������Ĺ��ܲ�ͬ
																		//����ʹ�õ���PWMģʽ���ȽϽ�����������ı�����ĵ�ƽ״̬�ġ�����д��0����һֱ����͵�ƽ
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//��ʼ�����ڶ�ʱ��3���������ͨ��
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //����Ԥװ�����ã�����дҲ���Բ�д
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);//ʹ������CNT��ʼ����
}

