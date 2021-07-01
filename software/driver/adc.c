#include "adc.h"
#include "uart.h"


__IO uint16_t ADC_ConvertedValue[2] = {0,0};

/**
  * @brief  ADC GPIO 初始化
  * @param  无
  * @retval 无
  */
static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = 	ADC_PIN1|ADC_PIN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);				
}

/**
  * @brief  配置ADC工作模式
  * @param  无
  * @retval 无
  */
static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( u32 ) ( & ( ADC_x->DR ) );
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 2;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;	

	ADC_Init(ADC_x, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL1, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL2, 2, ADC_SampleTime_239Cycles5);

	ADC_DMACmd(ADC_x, ENABLE);
	ADC_Cmd(ADC_x, ENABLE); 
	ADC_ResetCalibration(ADC_x);

	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	ADC_StartCalibration(ADC_x);
	while(ADC_GetCalibrationStatus(ADC_x));
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}

/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void adc_init(void)
{
	ADC1_GPIO_Config();
	ADCx_Mode_Config();

}




void adc_print_vol(void)
{
	float ADC_ConvertedValueLocal[2];
	ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0];
	ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1];	
	
	printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
	printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);		
	
	delay_ms(300);
}



/*********************************************END OF FILE**********************/






