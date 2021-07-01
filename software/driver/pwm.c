#include "pwm.h"


void pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 7199; //计数周期，向上记到此数，计数值清零
    TIM_TimeBaseStructure.TIM_Prescaler = 0;//定时器分频系数，Ftimer = 72M/(TIM_Prescaler+1) = 1ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//与死区时间分频有关
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	
	


    TIM_OCInitTypeDef        TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 3600;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);	
	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);	

    /* Time base configuration */
	TIM_BDTRInitTypeDef      TIM_BDTRInitStruct;

    /****** 配置BDTR寄存器，配置死区时间****************/
    /*
       定时器时钟 72M   TIM_ClockDivision = TIM_CKD_DIV1时,  Tdts = 13.89ns
       0 - 1.764us  用算法一
       1.778us - 3.505us  用算法二
       3.556us - 7.000us  用算法三
       7.1117us - 14us    用算法四
       需要更长时间,使用TIM_ClockDivision分频
    */
    TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct.TIM_DeadTime = 72; //死区时间  72:1us 172:3us 205:5us
    TIM_BDTRConfig(TIM1,&TIM_BDTRInitStruct);

//    TIM1->BDTR |= 72;   //设置死区  注:上面那种方法也可以，这种快且简单


    /* TIM1 enable counter */
    TIM_Cmd(TIM1, ENABLE);//使能定时器1

    TIM_CtrlPWMOutputs(TIM1, ENABLE);//使能PWM外围输出

}


/*
 *	percent百分比，0~99%，0~100
 *	dir方向，0左，1右
 *  percent和占空比关系 反相，保证低端MOS管关闭，高端MOS和占空比同步
*/
void pwm_set(u8 percent, u8 dir)
{
	// per0 
	u16 pwm = 7199 - percent*72;
	
	if(dir)
	{
		TIM_SetCompare1(TIM1,pwm);
		TIM_SetCompare2(TIM1,0);		//LO导通
	}
	else
	{
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare2(TIM1,pwm);	
	}
}


/*
转向电机
TIM1CH1,PA8
PC8.9控制方向
*/
void pwm_front_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
																		
	//设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	TIM_TimeBaseStructure.TIM_Period = 7199; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 

	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

	TIM_Cmd(TIM1, ENABLE);  //使能TIM1	
}


void pwm_front_set(u8 percent, u8 dir)
{
	u16 pwm = percent*72;
	if(dir)
	{
		PCout(8) = 1;
		PCout(9) = 0;
	}
	else
	{
		PCout(8) = 0;
		PCout(9) = 1;	
	}
	TIM_SetCompare1(TIM1,pwm);
}

