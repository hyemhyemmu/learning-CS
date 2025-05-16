#include "stm32f10x.h"                  // Device header

// 简单的点灯操作
int main(){
	/**
	*直接使用寄存器操作的方式：
	*RCC->APB2ENR = 0x00000010;
	*GPIOC->CRH = 0x00300000;
	*GPIOC->ODR = 0x00002000;
	*/
	
	// 下面是直接使用库函数的更简洁的方式
	// 配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // PC13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	// 开始点灯
	GPIO_SetBits(GPIOC, GPIO_Pin_1);
	//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	
	while(1)
	{
	}
}