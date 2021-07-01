#include "encoder.h"


void motor_encoder_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//输出端口时钟开启
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);


	//编码器输入引脚初始化，引脚分配参考电路图
	//PA0 PA1 PA6 PA7 PA15	PB3 PB6 PB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |
								  GPIO_Pin_7 ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |
								  GPIO_Pin_7 ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*引脚重映射，PA0/TIM2_CH1/TIM5_CH1	PA1/TIM2_CH2/TIM5_CH2
	把TIM2的CH1/CH2映射到PA15/PB3，其他不变，需要禁止JTAG输出*/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);	
	
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_ICInitTypeDef TIM_ICInitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
	TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;

	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

//未写中断服务函数
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM3,0);
	TIM_SetCounter(TIM4,0);
	
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE); 


}





