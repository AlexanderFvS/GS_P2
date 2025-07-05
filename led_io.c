#include "led_io.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"



void setLedD(int mask)
{
	GPIOD->ODR = mask & 0xFFu;
}


void resetLedD()
{
	GPIOD->ODR = 0;
}


void setLedE(Direction dir)
{
	switch(dir)
	{
		case FORWARDS:
			GPIOE->ODR = 0x01u << 7;
			break;
		
		case BACKWARDS:
			GPIOE->ODR = 0x01u << 6;
			break;
		
		case INVALID:
			GPIOE->ODR = 0x01u << 5;
			break;
		
		case NO_CHANGE:
			break;
	}
	
	
	
	
}


int readLedF()
{
	return GPIOG->IDR & 0x03u;
}


bool readButtonF(int offset)
{
	int maskSet = (0x01u << offset);
	int input = GPIOF->IDR;
	
	return maskSet != (input & maskSet);
}
