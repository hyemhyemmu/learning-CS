#include "stm32f10x.h"                  // Device header

void Init_AD(void){
	
	// 1. 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  //6分频
	
	// 2. 配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// 多通道，如果不用DMA转运，就需要每一次手动配置通道
	// 因此配置通道的代码放在取值的时候执行
	
	
	// 4. 初始化ADC
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; //连续
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE; //非扫描
	ADC_Init(ADC1, &ADC_InitStruct);
	
	
	ADC_Cmd(ADC1, ENABLE);
	
	// 5. 校准
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //启动
}


uint16_t AD_GetValue(uint8_t ADC_Channel){
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 
		1, ADC_SampleTime_1Cycles5);
	return ADC_GetConversionValue(ADC1); //读取
}
