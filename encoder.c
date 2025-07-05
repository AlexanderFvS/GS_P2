#include "encoder.h"
#include "led_io.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "timestamp.h"

											
Phase newPhase;
Phase currPhase;

volatile int currCount = 0;
volatile Direction currDir = NO_CHANGE;
volatile uint32_t currTimestamp = 0;

Direction transitions[4][4] =
{ //   A   |    D    |    B    |    C
	{NO_CHANGE, BACKWARDS, FORWARDS, INVALID}, // A 
	{FORWARDS, NO_CHANGE, INVALID, BACKWARDS}, // D
	{BACKWARDS, INVALID, NO_CHANGE, FORWARDS}, // B
	{INVALID, FORWARDS, BACKWARDS, NO_CHANGE}  // C
};



void initInterrupts()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;     // Clock for GPIO Port G
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;    // System conf. Clock enable
	// Routing Pin 0 of Port G -> EXTI0
	SYSCFG->EXTICR[0] &= ~(0x0f << (4 * 0)); // Remove old selection
	SYSCFG->EXTICR[0] |=   0x06 << (4 * 0);  // 0x06 : Select port G
	// Routing Pin 1 of Port G -> EXTI1
	SYSCFG->EXTICR[0] &= ~(0x0f << (4 * 1)); // Remove old selection
	SYSCFG->EXTICR[0] |=   0x06 << (4 * 1);  // 0x06 : Select port G
	
	EXTI->RTSR |= (1 << 0); // Select rising trigger for INT0
	EXTI->FTSR |= (1 << 0); // Select falling trigger for INT0
	EXTI->IMR  |= (1 << 0); // Unmask INT0
	EXTI->RTSR |= (1 << 1); // Select rising trigger for INT1
	EXTI->FTSR |= (1 << 1); // Select falling trigger for INT1
	EXTI->IMR  |= (1 << 1); // Unmask INT1
	
	NVIC_SetPriorityGrouping(0);  // Set up interrupt controller
	NVIC_SetPriorityGrouping(1);  // Set up interrupt controller
	NVIC_SetPriority(EXTI0_IRQn, 8);
	NVIC_SetPriority(EXTI1_IRQn, 8);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI0_IRQHandler(void) {
	currTimestamp = getTimeM();																// Zeitdifferenz berechnen
	setPhase();
	EXTI->PR = (1 << 0);  																		// Interrupt löschen
}

void EXTI1_IRQHandler(void) {
	currTimestamp = getTimeM();																// Zeitdifferenz berechnen
	setPhase();
	EXTI->PR = (1 << 1);  																		// Interrupt löschen
}




void setPhase()
{
	newPhase = readLedF();																		// Aktuelle Phase von den GPIOs lesen
	currDir = transitions[currPhase][newPhase];								// Richtung aus Tabelle bestimmen
		
	switch(currDir)
	{
		case FORWARDS:
			currCount++;
			
			break;
		
		case BACKWARDS:
			currCount--;
			
			break;
		
		case INVALID:
			
			break;
			 
		
		case NO_CHANGE:
			
			break;
	}
	currPhase = newPhase;
	
}


void resetCount()
{
	currCount = 0;
}

void setCurrPhase () {
	currPhase = readLedF();
}


