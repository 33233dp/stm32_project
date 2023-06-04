#ifndef __IF_Tracing_H__
#define __IF_Tracing_H__

/**红外寻迹模块引脚**/
#define IF1_PIN GPIO_Pin_5
#define IF2_PIN GPIO_Pin_6
#define IF3_PIN GPIO_Pin_14

#define IF1_PORT GPIOA
#define IF2_PORT GPIOA
#define IF3_PORT GPIOB

#define MIF_PORT GPIOA //中间
#define RIF_PORT GPIOA //右边
#define LIF_PORT GPIOB //左边
#define RRIF_PORT GPIOC //右右边
#define LLIF_PORT GPIOC //左左边
#define MIF_PIN GPIO_Pin_5
#define RIF_PIN GPIO_Pin_6
#define LIF_PIN GPIO_Pin_14
#define RRIF_PIN GPIO_Pin_2
#define LLIF_PIN GPIO_Pin_5

/*-----方向标志位------*/
#define MID 5
#define LFT 4
#define RIT 6

//循迹模块位置标志
#define LL IF[0] //最左
#define L IF[1]
#define M IF[2] //中间
#define R IF[3]
#define RR IF[4] //最右

//位置传递参数
#define PosM 0
#define PosR 1
#define PosRR 2
#define PosL -1
#define PosLL -2


/**红外寻迹模块时钟**/
#define IF1_RCC RCC_APB2Periph_GPIOA
#define IF2_RCC RCC_APB2Periph_GPIOA
#define IF3_RCC RCC_APB2Periph_GPIOB
#define RRIF_RCC RCC_APB2Periph_GPIOC
#define LLIF_RCC RCC_APB2Periph_GPIOC

extern uint8_t IF1_Flag;
extern uint8_t IF2_Flag;
extern uint8_t IF3_Flag;
extern int Pos,Erro;//当前位置，误差


void IF_TracingInit(void);
void IF_Start(void);//上电测试函数
int8_t IFPos_Read(void);//位置获取函数

#endif
