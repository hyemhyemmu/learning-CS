#include "stm32f10x.h"                  // Device header

void initLightSensor(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

uint8_t LightSensor_Get(){
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
