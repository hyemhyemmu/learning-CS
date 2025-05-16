#include "stm32f10x.h"                  // Device header

int16_t count = 0;

void InitCountSensor(){
	
	// 1. 配置时钟
	// 开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// 开启AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// NVIC作为内核外设，时钟默认开启，无需理会；
	// EXTI由NVIC控制，因此也不需要理会
	
	// 2.配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // 选择手册中推荐的上拉输入 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	// 3. 配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	
	// 4. 配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	// 5. 配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 优先级分组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =  1;
	NVIC_Init(&NVIC_InitStructure);
	
}

int16_t getCount_CountSensor(){
	return count;
}


void EXTI15_10_IRQHandler(){
	
	// 判断是否是14端口带来的中断
	if (EXTI_GetITStatus(EXTI_Line14) == SET){
		count ++;
		// 清除中断位
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
	
}