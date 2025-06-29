#ifndef LED_IO_H
#define LED_IO_H

#include <stdbool.h>
#include "encoder.h"

/*
 ****************************************************************************************
 *  @brief      Bekommt eine Bitmaske und schaltet die LEDs in GPIOF an, bzw. aus.
 *
 *  @param  		mask: int mit der Bitmaske
 *
 *  @return     void
 ****************************************************************************************/
 
void setLedD(int);

/*
 ****************************************************************************************
 *  @brief      Setzt alle LEDs in GPIOD wieder auf 0.
 *
 *
 *  @return     void
 ****************************************************************************************/

void resetLedD();

/*
 ****************************************************************************************
 *  @brief      Bekommt eine Bitmaske und schaltet die LEDs in GPIOF an, bzw. aus.
 *
 *  @param  		offset: int mit dem Offset der entsprechenden LED
 *
 *  @return     void
 ****************************************************************************************/

void setLedE(Direction dir);

/*
 ****************************************************************************************
 *  @brief      Liest die Inputs an GPIOF ein.
 *
 *
 *  @return     int: PF0, PF1
 ****************************************************************************************/

int readLedF();

/*
 ****************************************************************************************
 *  @brief      Prüft ob ein Input an GPIOF geschaltet ist.
 *
 *  @param  		offset: int mit dem Offsets des Inputs
 *
 *  @return     bool: true wenn geschaltet, false wenn nicht.
 ****************************************************************************************/

bool readButtonF(int);

#endif
