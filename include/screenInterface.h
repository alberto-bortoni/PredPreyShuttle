/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                           SCREEN INTERFACES                             */
/*-------------------------------------------------------------------------*/
#ifndef screenInterface_h
#define screenInterface_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <main.h>

//LiquidCrystal lcd(2, 3, 8, 9, 10, 11);
//LiquidCrystal *lcd;

/*_________________________________________________________________________*/
/***************************************************************************/

void initScreen();
void dispMsg(String tmsg, uint8_t trow);
String prepareMsg(String tstr);
void screenTest();

#endif
/*EOF*/