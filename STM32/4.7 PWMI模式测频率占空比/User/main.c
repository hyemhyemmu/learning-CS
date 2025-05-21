#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "IC.h"
#include <stdio.h>


int main(){
	Init_PWM();
	Init_IC();
	
	
	while(1){
		printf("%d\n", IC_GetFreq());
		printf("%d\n", IC_GetDuty());
	}
}

