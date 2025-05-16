#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Encoder.h"
#include <stdio.h>

int16_t num;

int main()
{
	InitEncoder();
	while(1){
		num += getEncoderCount();
		printf("%d", num);
	}
}
