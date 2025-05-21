#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void initKey(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

uint8_t Key_GetNum(){
	uint8_t curr = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0){
		// 低电平输入，也就是按键按下
		Delay_ms(20);
		
		// 如果长时间按下按钮
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);
		Delay_ms(20);
		curr = 1;
	}
	
	return curr;
}

