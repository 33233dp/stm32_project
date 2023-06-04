#ifndef __IF_Tracing_H__
#define __IF_Tracing_H__

/**����Ѱ��ģ������**/
#define IF1_PIN GPIO_Pin_5
#define IF2_PIN GPIO_Pin_6
#define IF3_PIN GPIO_Pin_14

#define IF1_PORT GPIOA
#define IF2_PORT GPIOA
#define IF3_PORT GPIOB

#define MIF_PORT GPIOA //�м�
#define RIF_PORT GPIOA //�ұ�
#define LIF_PORT GPIOB //���
#define RRIF_PORT GPIOC //���ұ�
#define LLIF_PORT GPIOC //�����
#define MIF_PIN GPIO_Pin_5
#define RIF_PIN GPIO_Pin_6
#define LIF_PIN GPIO_Pin_14
#define RRIF_PIN GPIO_Pin_2
#define LLIF_PIN GPIO_Pin_5

/*-----�����־λ------*/
#define MID 5
#define LFT 4
#define RIT 6

//ѭ��ģ��λ�ñ�־
#define LL IF[0] //����
#define L IF[1]
#define M IF[2] //�м�
#define R IF[3]
#define RR IF[4] //����

//λ�ô��ݲ���
#define PosM 0
#define PosR 1
#define PosRR 2
#define PosL -1
#define PosLL -2


/**����Ѱ��ģ��ʱ��**/
#define IF1_RCC RCC_APB2Periph_GPIOA
#define IF2_RCC RCC_APB2Periph_GPIOA
#define IF3_RCC RCC_APB2Periph_GPIOB
#define RRIF_RCC RCC_APB2Periph_GPIOC
#define LLIF_RCC RCC_APB2Periph_GPIOC

extern uint8_t IF1_Flag;
extern uint8_t IF2_Flag;
extern uint8_t IF3_Flag;
extern int Pos,Erro;//��ǰλ�ã����


void IF_TracingInit(void);
void IF_Start(void);//�ϵ���Ժ���
int8_t IFPos_Read(void);//λ�û�ȡ����

#endif
