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
#ifndef __LED_H
#define __LED_H

#include "system.h"

#define 	LED_STOP		PBout(12)	  
#define 	LED_SPEEDUP		PBout(14)
#define 	LED_SPEEDDOWN   PBout(13)



void led_init(void);
void led_status_display(u8 k);


#endif


