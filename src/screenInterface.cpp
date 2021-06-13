/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                           SCREEN INTERFACES                             */
/*-------------------------------------------------------------------------*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <screenInterface.h>
#include <main.h>

LiquidCrystal lcd(2, 3, 8, 9, 10, 11);

/*_________________________________________________________________________*/
/***************************************************************************/

void initScreen(){
  analogReference(EXTERNAL);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}
/*-------------------------------------------------------------------------*/

void dispMsg(String tmsg, uint8_t trow){
  if(trow == 1){
    lcd.setCursor(0, 0);
  }else{
    lcd.setCursor(0, 2);
  }

  lcd.print(prepareMsg(tmsg));
}
/*-------------------------------------------------------------------------*/

String prepareMsg(String tstr){
  if(tstr.length()>=16){
    tstr.substring(0,16);
  }else {
    for(uint8_t i = 0; i < (16 - tstr.length()); i++) {
        tstr += ' ';  
    }
  }
  return tstr;
}
/*-------------------------------------------------------------------------*/

String speedAndDelay(int speed, int delay){
  static const String speedStr = "S: ";
  static const String delayStr = " D: ";

  String outStr = speedStr + speed + delayStr + delay; 
  
  return outStr;
}
/*-------------------------------------------------------------------------*/

void screenTest(){
  lcd.noDisplay();
  delay(500);
  lcd.display();
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}
/*-------------------------------------------------------------------------*/

/*EOF*/