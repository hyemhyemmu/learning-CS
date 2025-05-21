#include "stm32f10x.h"                  // Device header
#include "AD.h"
#include <stdio.h>

uint16_t value;
float voltage;

int main()
{
	Init_AD();
	
	while(1){
		value = AD_GetValue();
		voltage = (float)value / 4095 * 3.3;
		printf("%d", value);
	}
}
