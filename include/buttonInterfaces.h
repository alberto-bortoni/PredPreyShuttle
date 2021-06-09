/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                           BUTTON INTERFACES                             */
/*-------------------------------------------------------------------------*/
#ifndef buttonInterfaces_h
#define buttonInterfaces_h

#include <Arduino.h>
#include <main.h>

uint8_t const upBttnPin    = 23;
uint8_t const dnBttnPin    = 22;
uint8_t const enBttnPin    = 37;
uint8_t const pauseBttnPin = 31;

/*_________________________________________________________________________*/
/***************************************************************************/

void initButtonInterfaces();
boolean upBtSt() ;
boolean downBtSt();
boolean enableBtSt();
boolean pauseBtSt();

#endif
/*EOF*/