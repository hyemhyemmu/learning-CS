#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MyDMA.h"

uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0, 0, 0};

int main()
{
	Init_DMA((uint32_t)DataA, (uint32_t)DataB, 4);
	
	while(1){
	
	}
}
