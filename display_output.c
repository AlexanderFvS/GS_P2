#include <stdio.h>
#include "display_output.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#define ArraySize 16

char altWinkel[ArraySize] = "";
char altGeschw[ArraySize] = "";

void printLabels()
{
	lcdGotoXY(1,1);
	lcdPrintS("Drehwinkel in Grad");
	
	lcdGotoXY(1,4);
	lcdPrintS("Drehgesch. in Grad/Sek.");
	
	
}

void printError()
{
	lcdGotoXY(1, 8);
	lcdPrintS("ERROR: INVALID STATE");
}

void clearError()
{
	lcdGotoXY(1, 8);
	lcdPrintS(" ");																						// Funktion löscht alles rechts vom Cursor
}

void printWinkel(double neuWinkel, int printCount)
{
	
	char neuTemp[ArraySize];
	sprintf(neuTemp, "%10.1f", neuWinkel);
	
	
	if (neuTemp[printCount] != altWinkel[printCount])
	{
		lcdGotoXY((1 + printCount), 2);
		char print = neuTemp[printCount];
		lcdPrintC(print);
	}
	altWinkel[printCount] = neuTemp[printCount];
}

	


void printGeschw(double neuGeschw, int printCount)
{
	
	char neuTemp[ArraySize];
	sprintf(neuTemp, "%10.3f", neuGeschw);
	
	
	if (neuTemp[printCount] != altGeschw[printCount])
	{
		lcdGotoXY((1 + printCount), 5);
		char print = neuTemp[printCount];
		lcdPrintC(print);
	}
	altGeschw[printCount] = neuTemp[printCount];
}
