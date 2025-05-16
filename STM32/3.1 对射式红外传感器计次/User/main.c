#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "CountSensor.h"
#include <stdio.h>


int main()
{
	while(1){
		uint16_t num = getCount_CountSensor();
		printf("%d", num);
	}
}
