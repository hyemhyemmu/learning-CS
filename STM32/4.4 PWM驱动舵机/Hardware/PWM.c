#include "stm32f10x.h"                  // Device header

// 使用PA1的通道2 （为了避开刚刚呼吸灯可能的冲突）

void Init_PWM(void){
	// 1. 打开RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// 2. 选择时基单元的时钟
	TIM_InternalClockConfig(TIM2);
	
	// 3. 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //采样1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1; //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 只有高级定时器才有
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 4. 初始化比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// 为了避免有些初始值没有被赋予带来的错误，先给结构体赋予一个初始值
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; //CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	
	TIM_Cmd(TIM2, ENABLE);
	
}


// 封装一下PWM的置位函数
void PWM_SetCompare(uint16_t Compare){
	TIM_SetCompare2(TIM2, Compare);
}