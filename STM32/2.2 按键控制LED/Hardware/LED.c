#include "stm32f10x.h"                  // Device header


// 初始化A1, A2
void initLED(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// 高电平触发，所以先置位以初始化为熄灭
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void LED1_turn(){
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) ==0){
		// 读取上一位设置的位，这一次就反过来设置
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}

void LED2_turn(){
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) ==0){
		// 读取上一位设置的位，这一次就反过来设置
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}

