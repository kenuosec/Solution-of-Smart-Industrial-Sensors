/*
 *	system.c
 * 	2020-07-31 10:02:39
 * 	
 * 	包含的功能:
 *		1.软件延时功能
 *		2.GPIO的类51引脚操作宏定义
 *		3.中断开关汇编函数
 *		
 *
 */
#include "system.h"



static __IO u32 TimingDelay;
 
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void delay_init(void)
{
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   us延时程序,10us为一个单位
  * @param  
  *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 10us = 10us
  * @retval  无
  */
void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}


void delay_us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	
	for(i=0;i<us;i++)
	{
		// 当计数器的值减小到0的时候，CRTL寄存器的位16会置1	
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// 关闭SysTick定时器
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

void delay_ms( __IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SystemCoreClock/1000);
	
	for(i=0;i<ms;i++)
	{
		// 当计数器的值减小到0的时候，CRTL寄存器的位16会置1
		// 当置1时，读取该位会清0
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// 关闭SysTick定时器
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}


void delay_s( __IO uint32_t s)
{
	uint32_t i;
	for(i=0;i<s;i++)
		delay_ms(1000);
}







void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
