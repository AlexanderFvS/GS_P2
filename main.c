#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "LCD_GUI.h"
#include "init.h"
#include "lcd.h"
#include "encoder.h"
#include "display_output.h"
#include "angle.h"
#include "timestamp.h"
#include "led_io.h"
#include "delay.h"

#define ZEITFENSTER 250.0												// Zeitfenster für Geschwindigkeitsberechnung in Sekunden



int main()
{
	initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);
	lcdSetFont(20);
	
	printLabels();																// Initialisierung
	initTimeM();
	int lastTimestamp = getTimeM();					
	int lastCount = 0;
	double winkel1;
	double geschw1;
	int printCount = 0;
	setCurrPhase();
	initInterrupts();
	
	
	
	
	//____________________________________Superloop____________________________________________//
	
	
	while (1)
	{
		//int a = getTimeM();
		//GPIOE->BSRR = (0x01U);															// Oszilloskop  D16
		currTimestamp = getTimeM();
																													// --Error Abfrage--
		if (currDir == INVALID)																// Encoder-Status abfragen (gibt -1 zurück bei Fehler somit true)
		{
			printError();
			setLedE(currDir);
			while (!readButtonF(6)) {}													// Warte so lange bis S6 gedrückt wird. Dann Reset Error
			clearError();
			resetCount();
			setCurrPhase();
		}
		
		
		
		double period = getPeriodM(lastTimestamp, currTimestamp);							// -------Verarbeitung-------
		
		if (period > (ZEITFENSTER + 50.0) || (period > ZEITFENSTER && currDir != NO_CHANGE)) {						// Nur berechnen und drucken wenn genug Zeit vergangen ist (ZEITFENSTER)
			
			printCount = 0;
			
			winkel1 = calcWinkel();
			geschw1 = calcGeschw(lastCount, currCount, period);
																													// Werte für nächsten Durchlauf aktualisieren
			lastTimestamp = currTimestamp;	
			lastCount = currCount;
			
		}
		if (currDir != NO_CHANGE) {
			setLedD(currCount);																		// ------Ausgabe------
			setLedE(currDir);
		}
		
		
		if (printCount < 20) {																
			if (printCount < 10) {
				printWinkel(winkel1, printCount);	
			} else {
				printGeschw(geschw1, printCount - 10);
			}
			printCount++;
		}
				
		//GPIOE->BSRR = (0x01U << 16);													// Oszilloskop
		//int b = getTimeM();
		printf("Encoder Count: %d\n", currCount);
		
		
		}
}
