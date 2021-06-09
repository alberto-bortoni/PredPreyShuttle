/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                           BUTTON INTERFACES                             */
/*-------------------------------------------------------------------------*/

#include <Arduino.h>
#include <buttonInterfaces.h>
#include <main.h>

/*_________________________________________________________________________*/
/***************************************************************************/

void initButtonInterfaces(){
  pinMode(upBttnPin, INPUT_PULLUP);
  pinMode(dnBttnPin, INPUT_PULLUP);
  pinMode(enBttnPin, INPUT_PULLUP);
  pinMode(pauseBttnPin, INPUT_PULLUP);
}
/*-------------------------------------------------------------------------*/

boolean upBtSt() {
  return !digitalRead(upBttnPin);
}
/*-------------------------------------------------------------------------*/

boolean downBtSt() {
  return !digitalRead(dnBttnPin);
}
/*-------------------------------------------------------------------------*/

boolean enableBtSt() {
  return digitalRead(enBttnPin);
}
/*-------------------------------------------------------------------------*/

boolean pauseBtSt() {
  return !digitalRead(pauseBttnPin);
}
/*-------------------------------------------------------------------------*/

/*EOF*/