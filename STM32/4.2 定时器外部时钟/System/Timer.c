#include "stm32f10x.h"                  // Device header

// 外部时钟用的是A0端口

/*
	初始化TIM2，也就是通用定时器
*/
void Init_Timer(void){
	// 1. 打开RCC和GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, 
	
	// 2. 选择时基单元的时钟 - 外部时钟
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, 
		TIM_ExtTRGPolarity_NonInverted,
		0x00);
	
	// 3. 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //采样1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 只有高级定时器才有
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 去除TimeBaseInit强制更新带来的预设位
	TIM_ClearFlag(TIM2, TIM_IT_Update);

	// 4. 使能更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	
	// 5. 配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	// 6. 启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

/*
// 中断函数
void TIM2_IRQHANDLER(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}		
}
*/