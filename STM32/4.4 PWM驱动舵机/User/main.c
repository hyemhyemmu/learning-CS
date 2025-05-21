#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"


int main()
{
	Init_Servo();
	
	while(1){
		// 根据需要调用void Servo_SetAngle(float angle);
	}
}

