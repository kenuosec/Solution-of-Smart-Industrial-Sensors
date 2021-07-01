/*
 *	led.c
 * 	2020-07-31 10:17:14
 * 	
 * 	实现功能: 
 *		led初始化开关
 *
 *
 *
 *
 */
#include "led.h"



/* ---------------------------- 方法实现 ------------------------------------ */
void led_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;		
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
    GPIO_Init(GPIOB, &GPIO_InitStructure);	

}


void led_status_display(u8 k)
{
	if(k == 0)
	{
		LED_STOP 		= 1;
		LED_SPEEDUP 	= 0;
		LED_SPEEDDOWN 	= 0;
	}
	else if(k>50)
	{
		LED_STOP 		= 0;
		LED_SPEEDUP 	= 1;
		LED_SPEEDDOWN 	= 0;
	}
	else	/*k<50被限速*/
	{
		LED_STOP 		= 0;
		LED_SPEEDUP 	= 0;
		LED_SPEEDDOWN 	= 1;	
	}

}


