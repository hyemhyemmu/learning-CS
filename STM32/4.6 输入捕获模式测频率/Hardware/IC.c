#include "stm32f10x.h"                  // Device header

void Init_IC(void){
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// 2. 选择时基单元的时钟
	TIM_InternalClockConfig(TIM3);
	
	// 3. 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //采样1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 只有高级定时器才有
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	// 4. 初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //使用通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿触发
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //不交叉
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	// 5. 配置触发源
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	
	// 6. 配置从模式
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	// 7. 总体启动
	TIM_Cmd(TIM2, ENABLE);
}

uint32_t IC_GetFreq(void){
	return 1000000 / TIM_GetCapture1(TIM3);
}
