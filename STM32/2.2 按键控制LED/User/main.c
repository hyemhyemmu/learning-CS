#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "key.h"

int main()
{
	initLED();
	initKey();
	
	uint8_t KeyNum;
	
	while(1){
		KeyNum = Key_GetNum();
		if (KeyNum)
			LED1_turn();
	}
}
