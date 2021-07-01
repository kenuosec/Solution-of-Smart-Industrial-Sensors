#include "uart.h"	  

#define		PRINTF_UASRT	USART1


/* -------------------------    UART1,调试信息输出    -------------------------- */
void uart1_init(u32 baud)
{
	/* 中断配置 */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel 					 = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	/* 引脚配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin	  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	/* 工作模式配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate 		      = baud;
	USART_InitStructure.USART_WordLength 		  = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 			  = USART_StopBits_1;
	USART_InitStructure.USART_Parity 			  = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 				  = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	

	// 使能串口接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART1, ENABLE);	
  // 清除发送完成标志
	//USART_ClearFlag(USART1, USART_FLAG_TC);     
}






/* -------------------------    UART2,EC200数据传输    -------------------------- */
void uart2_init(u32 baud)
{
	/* 中断配置 */
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel 					 = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	/* 引脚配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin	  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	/* 工作模式配置 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate 		      = baud;
	USART_InitStructure.USART_WordLength 		  = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 			  = USART_StopBits_1;
	USART_InitStructure.USART_Parity 			  = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 				  = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	

	/* 使能 */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART2, ENABLE);	

}



/* -------------------------    数据发送函数的封装    -------------------------- */
/* 发送一个字节 */
void uart_sendbyte(USART_TypeDef* pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	/* 等待发送数据寄存器为空 */
}

/* 发送8位数组 */
void uart_sendarray(USART_TypeDef* pUSARTx, uint8_t *array, uint16_t num)
{
	uint8_t i;
	for(i=0; i<num; i++)
	{
		USART_SendData(pUSARTx,array[i]);
		while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	/* sendbyte */
	}
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*  发送字符串 */
void uart_sendstring(USART_TypeDef* pUSARTx, char *str)
{
	unsigned int k=0;
	do 
	{
		uart_sendbyte( pUSARTx, *(str + k) );
		k++;
	} 
	while(*(str + k)!='\0');
  
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

void uart_sendword( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/* -------------------------    printf函数的支持    -------------------------- */
#pragma import(__use_no_semihosting)             
  
struct __FILE 
{ 
	int handle;
}; 

FILE __stdout;       
  
void _sys_exit(int x) 	//定义_sys_exit()以避免使用半主机模式  
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)		//重定义fputc函数
{      
	while((PRINTF_UASRT->SR&0X40)==0) {};	//循环发送,直到发送完毕   
    PRINTF_UASRT->DR = (u8) ch;      
	return ch;
}



/* -------------------------    串口2printf函数的支持    -------------------------- */
/* 发送数据的缓冲区 */
char uart2_tx_buf[1024];

void printf2(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)uart2_tx_buf,fmt,ap);	
	va_end(ap);	
	uart_sendstring(USART2, uart2_tx_buf);
}



/* -------------------------    串口1中断服务程序    -------------------------- */

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   
#define USART_REC_LEN  			200
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA = 0;       //接收状态标记	

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据

		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)
					USART_RX_STA=0;//接收错误,重新开始
				else 
					USART_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{
				if(Res==0x0d)
					USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;//接收数据错误,重新开始接收	  
				} 
			}
		}
	}
}

