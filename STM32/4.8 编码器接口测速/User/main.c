#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Encoder.h"
#include <stdio.h>

int main()
{
	Init_Encoder();
	
	while(1){
		printf("%d", Encoder_Get());
		Delay_ms(500);
	}
}
