#ifndef __GPIO_H
#define __GPIO_H

#include "system.h"


/*--------------------   GPIO引脚分配   ------------------*/

/* 4G模块电源 */
#define		EC200_POWER_PORT	GPIOA
#define		EC200_POWER_PIN		GPIO_Pin_1
#define 	EC200_POWER_CLK		RCC_APB2Periph_GPIOA

/* 4G模块复位 */
#define		EC200_RESET_PORT	GPIOA
#define		EC200_RESET_PIN		GPIO_Pin_5
#define 	EC200_RESET_CLK		RCC_APB2Periph_GPIOA

/* LED0 */
#define		LED0_PORT			GPIOB
#define		LED0_PIN			GPIO_Pin_0
#define 	LED0_PORT_CLK		RCC_APB2Periph_GPIOB

/* LED1 */
#define		LED1_PORT			GPIOB
#define		LED1_PIN			GPIO_Pin_1
#define 	LED1_PORT_CLK		RCC_APB2Periph_GPIOB

/* LED2 */
#define		LED2_PORT			GPIOB
#define		LED2_PIN			GPIO_Pin_2
#define 	LED2_PORT_CLK		RCC_APB2Periph_GPIOB

/* 用于LED状态控制的宏定义 */
#define 	ON		0
#define 	OFF		1

/* RELAY1 */
#define		RELAY1_PORT			GPIOC
#define		RELAY1_PIN			GPIO_Pin_9
#define 	RELAY1_PORT_CLK		RCC_APB2Periph_GPIOC

/* RELAY2 */
#define		RELAY2_PORT			GPIOC
#define		RELAY2_PIN			GPIO_Pin_8
#define 	RELAY2_PORT_CLK		RCC_APB2Periph_GPIOC

/* RELAY3 */
#define		RELAY3_PORT			GPIOC
#define		RELAY3_PIN			GPIO_Pin_7
#define 	RELAY3_PORT_CLK		RCC_APB2Periph_GPIOC

/* RELAY4 */
#define		RELAY4_PORT			GPIOC
#define		RELAY4_PIN			GPIO_Pin_6
#define 	RELAY4_PORT_CLK		RCC_APB2Periph_GPIOC



/*--------------------------   外部接口   --------------------------*/


void gpio_init(void);

/*---------   GPIO控制操作   -----------*/

/* 4G模块电源使能		1-工作  0-不工作 */
#define		EC200_POWER(n)		GPIO_WriteBit(EC200_POWER_PORT, EC200_POWER_PIN, (BitAction)n);

/* 4G模块复位			1-工作  0-复位 */
#define		EC200_RESET(n)		GPIO_WriteBit(EC200_RESET_PORT, EC200_RESET_PIN, (BitAction)n);


/* LED		1-灭 0-亮 */
#define 	LED0(n)				GPIO_WriteBit(LED0_PORT, LED0_PIN, (BitAction)n)  
#define 	LED1(n)				GPIO_WriteBit(LED1_PORT, LED1_PIN, (BitAction)n)  
#define 	LED2(n)				GPIO_WriteBit(LED2_PORT, LED2_PIN, (BitAction)n)



/* RELAY	1-通 0-断 */
#define 	RELAY1(n)			GPIO_WriteBit(RELAY1_PORT, RELAY1_PIN, (BitAction)n)  
#define 	RELAY2(n)			GPIO_WriteBit(RELAY2_PORT, RELAY2_PIN, (BitAction)n) 
#define 	RELAY3(n)			GPIO_WriteBit(RELAY3_PORT, RELAY3_PIN, (BitAction)n) 
#define 	RELAY4(n)			GPIO_WriteBit(RELAY4_PORT, RELAY4_PIN, (BitAction)n) 




#endif




