#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void initBuzzer(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void Buzzer_turn(){
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) ==0){
		// 读取上一位设置的位，这一次就反过来设置
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
}

void Buzzer_on(){
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_off(){
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}