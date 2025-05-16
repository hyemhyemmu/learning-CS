#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Timer.h"
#include <stdio.h>

uint16_t num = 0;

int main()
{
	Init_Timer();
	
	while(1){
		printf("%d", num);
		Delay_ms(500);
	}
}

// 中断函数
void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}		
}