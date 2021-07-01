/*
 *	uart.h
 * 	2020-07-31 09:33:24
 * 	
 *
 */
#ifndef __UART_H
#define __UART_H

#include "system.h"
#include <stdio.h>
#include <stdarg.h>





void uart1_init(u32 baud);
void uart2_init(u32 baud);
void uart_sendbyte(USART_TypeDef* pUSARTx, uint8_t ch);
void uart_sendarray(USART_TypeDef* pUSARTx, uint8_t *array, uint16_t num);
void uart_sendstring(USART_TypeDef* pUSARTx, char *str);



/* 自己实现的printf全局函数 */
void printf2(const char *fmt,...);

#endif


