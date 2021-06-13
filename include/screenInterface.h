/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                           SCREEN INTERFACES                             */
/*-------------------------------------------------------------------------*/
#ifndef screenInterface_h
#define screenInterface_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <main.h>


/*_________________________________________________________________________*/
/***************************************************************************/

void initScreen();
void dispMsg(String tmsg, uint8_t trow);
String prepareMsg(String tstr);
String speedAndDelay(int speed, int delay);
void screenTest();

#endif
/*EOF*/