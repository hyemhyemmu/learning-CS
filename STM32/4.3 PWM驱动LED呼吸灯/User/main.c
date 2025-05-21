#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"

uint16_t i;

int main()
{
	Init_PWM();
	
	while(1){
		for (i = 0; i <= 100; i++){
			PWM_SetCompare(i);
			Delay_ms(10);
		}
		
		for (i = 0; i <= 100; i++){
			PWM_SetCompare(100 - i);
			Delay_ms(10);
		}
	}
}

