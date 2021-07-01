/*
 *	gpio.c
 * 	2020-08-17 10:49:32
 *
 *
 */
#include "gpio.h"

/*
 *	通用GPIO初始化
 * 	GPIO分配
 *
 *	4G电源使能		PA1		外接了信号驱动电路  推挽输出   1-电源输出   0-无输出
 *	4G模块复位		PA5		RC复位电路上拉1.8V  开漏输出   1-工作       0-复位
 *
 *	LED0	PB0 
 *	LED0	PB1 
 *	LED0	PB2 
 *
 */
void gpio_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* 关闭JTAG下载功能 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	
	/* 4G模块电源使能 */	
	RCC_APB2PeriphClockCmd(EC200_POWER_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = EC200_POWER_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(EC200_POWER_PORT, &GPIO_InitStructure);
	
	GPIO_WriteBit(EC200_POWER_PORT, EC200_POWER_PIN, (BitAction)0);	/* 初始关闭输出 */
	
	
	/* 4G模块复位 */	
	RCC_APB2PeriphClockCmd(EC200_RESET_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = EC200_RESET_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(EC200_RESET_PORT, &GPIO_InitStructure);
	
	GPIO_WriteBit(EC200_RESET_PORT, EC200_RESET_PIN, (BitAction)1);	/* 初始不复位 */	
	
	
	/* LED0 */	
	RCC_APB2PeriphClockCmd(LED0_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED0_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(LED0_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(LED0_PORT, LED0_PIN, (BitAction)1);					/* 初始不亮 */
	
	
	/* LED1 */	
	RCC_APB2PeriphClockCmd(LED1_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED1_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(LED1_PORT, LED1_PIN, (BitAction)1);					/* 初始不亮 */


	/* LED2 */	
	RCC_APB2PeriphClockCmd(LED0_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED2_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(LED2_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(LED2_PORT, LED2_PIN, (BitAction)1);					/* 初始不亮 */
	
	
	/* RELAY1 */	
	RCC_APB2PeriphClockCmd(RELAY1_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = RELAY1_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(RELAY1_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(RELAY1_PORT, RELAY1_PIN, (BitAction)0);				/* 初始断开 */	
	
	
	/* RELAY2 */	
	RCC_APB2PeriphClockCmd(RELAY2_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = RELAY2_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(RELAY2_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(RELAY2_PORT, RELAY2_PIN, (BitAction)0);				/* 初始断开 */	
	
	
	/* RELAY3 */	
	RCC_APB2PeriphClockCmd(RELAY3_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = RELAY3_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(RELAY3_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(RELAY3_PORT, RELAY3_PIN, (BitAction)0);				/* 初始断开 */	
	
	
	/* RELAY4 */	
	RCC_APB2PeriphClockCmd(RELAY4_PORT_CLK, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = RELAY4_PIN;		
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		
    GPIO_Init(RELAY4_PORT, &GPIO_InitStructure);	
	
	GPIO_WriteBit(RELAY4_PORT, RELAY4_PIN, (BitAction)0);				/* 初始断开 */		
}


