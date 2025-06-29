#include "encoder.h"
#include "led_io.h"

int count = 0;															// Zählvariable für Encoder-Position


Direction transitions[4][4] =
{ //   A   |    D    |    B    |    C
	{NO_CHANGE, BACKWARDS, FORWARDS, INVALID}, // A 
	{FORWARDS, NO_CHANGE, INVALID, BACKWARDS}, // D
	{BACKWARDS, INVALID, NO_CHANGE, FORWARDS}, // B
	{INVALID, FORWARDS, BACKWARDS, NO_CHANGE}  // C
};

int setPhase(int newPhase, int currPhase,Direction* dir)
{
	
	Direction currDir = transitions[currPhase][newPhase];			// Richtung aus Tabelle bestimmen
		
	switch(currDir)
	{
		case FORWARDS:
			count++;
			
			break;
		
		case BACKWARDS:
			count--;
			
			break;
		
		case INVALID:
			count = 0;
			*dir = currDir;
			return -1;					// Fehler
		
		case NO_CHANGE:
			break;
	}
	
	*dir = currDir;
	return 0;								// kein Fehler
}

int getCount()
{
	return count;
}

void resetCount()
{
	count = 0;
}
