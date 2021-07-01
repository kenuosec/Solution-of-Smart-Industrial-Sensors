#include "vr.h"



u8 VR_message_buf[20];
u8 VR_data_flag = 0;  		

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	static u8 i = 0;
	u8 Res;
	
	//中断置位且缓存未满
	if( (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET))
	{
		Res = USART_ReceiveData(USART1);
		VR_message_buf[i] = Res;
		
		if(VR_message_buf[0] == 0x55)	//是正确的数据帧情况下
			i++;
		else
			i = 0;
	}	
	
	if(i == 3) 
	{
		i = 0;
		VR_data_flag = 1;		
	}
} 

