/*
 *	time.c
 * 	2020-08-17 12:48:38
 * 	
 * 	实现功能: 
 *		定时器6进行10ms定时，来判断两个数据包
 *
 *
 *
 *
 */
#include "time.h"


void time_init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 	
    NVIC_InitStructure.NVIC_IRQChannel 					 = TIM6_IRQn ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
    NVIC_Init(&NVIC_InitStructure);		

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    TIM_TimeBaseStructure.TIM_Period 					= (20-1);		/* (200-1)100ms中断一次，20ms控制一次 */
    TIM_TimeBaseStructure.TIM_Prescaler					= (36000-1);
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    	
	//TIM_Cmd(TIM6, ENABLE);
}


/*
 *	开始从0计时10ms
 *
 *
 *
 */
void time_start(void)
{
	TIM_SetCounter(TIM6,0);
	TIM_Cmd(TIM6, ENABLE);
}


void time_stop(void)
{
	TIM_Cmd(TIM6, DISABLE);
}



u8 time_10msflag = 0;
void TIM6_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) 
	{
		time_10msflag++;
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}


