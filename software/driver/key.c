#include "key.h"


void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTC时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
}


u8 key_get(void)
{	 
	if(PEin(3)==0)
	{
		delay_ms(10);
		if(PEin(3)==0)
			return 1;
	}
	
	
	if(PEin(4)==0)
	{
		delay_ms(10);
		if(PEin(4)==0)
			return 0;
	}
	
	if(PAin(0) == 1)
	{
		delay_ms(10);
		if(PAin(0) == 1)
			return 2;	
	}
	
	return 99;
}


