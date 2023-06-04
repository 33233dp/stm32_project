#include "main.h"                  // Device header
#include "IF_Tracing.h"

uint8_t IF1_Flag;
uint8_t IF2_Flag;
uint8_t IF3_Flag;

u8 IF[5] = {0};

int Pos,Erro;//当前位置，误差

void IF_TracingInit(void)
{
	GPIO_InitTypeDef IF_Structure;
	
	IF_Structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	IF_Structure.GPIO_Pin  = IF1_PIN |IF2_PIN|IF3_PIN|GPIO_Pin_5|GPIO_Pin_2;
	IF_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	RCC_APB2PeriphClockCmd(IF1_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(IF2_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(IF3_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(RRIF_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LLIF_RCC,ENABLE);
	
	GPIO_Init(IF1_PORT,&IF_Structure);
	GPIO_Init(IF2_PORT,&IF_Structure);
	GPIO_Init(IF3_PORT,&IF_Structure);
	GPIO_Init(GPIOC,&IF_Structure);
	GPIO_Init(GPIOC,&IF_Structure);
}

int8_t IFPos_Read(void)//位置获取函数
{

	
	L = GPIO_ReadInputDataBit(LIF_PORT,GPIO_Pin_14);
	M = GPIO_ReadInputDataBit(MIF_PORT,GPIO_Pin_5);
	R = GPIO_ReadInputDataBit(RIF_PORT,GPIO_Pin_6);
	LL = GPIO_ReadInputDataBit(LLIF_PORT,GPIO_Pin_5);
	RR = GPIO_ReadInputDataBit(RRIF_PORT,GPIO_Pin_2);
	/*-------OLED显示位置------*/
//	OLED_ShowNum(4,1+3,LL,1);
//	OLED_ShowNum(4,2+3,L,1);
//	OLED_ShowNum(4,3+3,M,1);
//	OLED_ShowNum(4,4+3,R,1);
//	OLED_ShowNum(4,5+3,RR,1);
	
	//M
	if(LL == 1 && L == 1 && M == 0 && R == 1 && RR == 1) {Erro = 0;Pos = PosM;}
	if(LL == 0 && L == 1 && M == 0 && R == 1 && RR == 1) {Erro = 0;Pos = PosM;}
	if(LL == 0 && L == 1 && M == 0 && R == 1 && RR == 0) {Erro = 0;Pos = PosM;}
	//R
	if(LL == 1 && L == 1 && M == 1 && R == 0 && RR == 1) {Erro = 1;Pos = PosR;}
	if(LL == 1 && L == 1 && M == 1 && R == 0 && RR == 0) {Erro = 1;Pos = PosR;}
	if(LL == 1 && L == 1 && M == 0 && R == 0 && RR == 1) {Erro = 1;Pos = PosR;}
	if(LL == 1 && L == 1 && M == 0 && R == 0 && RR == 0) {Erro = 1;Pos = PosR;}
	//RR
	if(LL == 1 && L == 1 && M == 1 && R == 1 && RR == 0) {Erro = 4;Pos = PosRR;}
	if(LL == 1 && L == 1 && M == 1 && R == 0 && RR == 0) {Erro = 4;Pos = PosRR;}
	if(LL == 1 && L == 1 && M == 0 && R == 1 && RR == 0) {Erro = 4;Pos = PosRR;}
	//L
	if(LL == 1 && L == 0 && M == 1 && R == 1 && RR == 1) {Erro = -1;Pos = PosL;}
	if(LL == 0 && L == 0 && M == 1 && R == 1 && RR == 1) {Erro = -1;Pos = PosL;}
	if(LL == 0 && L == 0 && M == 0 && R == 1 && RR == 1) {Erro = -1;Pos = PosL;}
	if(LL == 1 && L == 0 && M == 0 && R == 1 && RR == 1) {Erro = -1;Pos = PosL;}
	if(LL == 0 && L == 0 && M == 0 && R == 1 && RR == 1) {Erro = -1;Pos = PosL;}
	//LL
	if(LL == 0 && L == 1 && M == 1 && R == 1 && RR == 1) {Erro = -4;Pos = PosLL;}
	if(LL == 0 && L == 0 && M == 1 && R == 1 && RR == 1) {Erro = -4;Pos = PosLL;}	
	if(LL == 0 && L == 1 && M == 0 && R == 1 && RR == 1) {Erro = -4;Pos = PosLL;}
	if(LL == 0 && L == 0 && M == 0 && R == 1 && RR == 1) {Erro = -4;Pos = PosLL;}

	return Pos;
}

void IF_Start(void)//上电测试函数
{
	IF_TracingInit();
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)) IF1_Flag = 4;
	else IF1_Flag = 0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)) IF2_Flag = 6;
	else IF2_Flag = 0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6))	IF3_Flag = 5;
	else IF3_Flag = 0;
}
