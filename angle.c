#include "angle.h"
#include "encoder.h"
#include "timestamp.h"
#include "stm32f4xx_hal.h"

// 300 Schlitze = 1200 Phasenwechsel pro Umdrehung
#define WINKEL_PRO_SCHRITT 0.3

double calcWinkel()
{
	return getCount() * WINKEL_PRO_SCHRITT;
}

double calcGeschw(int count1, int count2, double periode)
{
	double steps = (double) count2 - count1;
	
	return (steps / (periode/ 1000)) * WINKEL_PRO_SCHRITT;
	
}
