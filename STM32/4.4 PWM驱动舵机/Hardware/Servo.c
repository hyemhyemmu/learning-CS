#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Init_Servo(void){
	Init_PWM();
}


void Servo_SetAngle(float angle){
	PWM_SetCompare(angle / 180 * 2000 + 500);
}