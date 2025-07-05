#ifndef ENCODER_H
#define ENCODER_H

#include "timestamp.h"

typedef enum
{
	PHASE_A = 0x00u,											// Hier werden die Phasen mit einem Enum in der richtigen Reihenfolge benannt.
	PHASE_B = 0x10u,
	PHASE_C = 0x11u,
	PHASE_D = 0x01u
} Phase;

typedef enum
{
	FORWARDS,															// Hier werden alle 4 States mit einem Enum definiert.
	BACKWARDS,
	INVALID,
	NO_CHANGE
} Direction;

extern volatile int currCount; 				// Zählvariable für Encoder-Position
extern volatile Direction currDir;
extern volatile uint32_t currTimestamp;





/*
 ****************************************************************************************
 *  @brief      Initialisiert beide Interrupts
 *
 *  @return     void
 ****************************************************************************************/

void initInterrupts();


/*
 ****************************************************************************************
 *  @brief      Liest die aktuelle Phase ein und vergleicht sie mit der letzten Phase.
 *              Verändert je nacht State den Counter und schaltet die entsprechenden LEDs an.
 *
 *  @return     int: returnt 0 wenn ok und -1 bei Error State.
 ****************************************************************************************/

void setPhase(void);


/*
 ****************************************************************************************
 *  @brief      Setzt den Counter wieder auf 0.
 *
 *  @return     void
 ****************************************************************************************/

void resetCount();

void setCurrPhase ();



#endif
