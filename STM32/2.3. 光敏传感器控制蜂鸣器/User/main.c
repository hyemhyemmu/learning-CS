#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Lightsensor.h"
#include "Buzzer.h"

int main()
{
	initLightSensor();
	initBuzzer();
	
	while(1){
		if (LightSensor_Get() < 100)
			Buzzer_on();
		else
			Buzzer_off();
	}
}
