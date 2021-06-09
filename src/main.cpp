/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                              SHUTTLE MOTH                               */
/*-------------------------------------------------------------------------*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <shuttleMotor.h>
#include <buttonInterfaces.h>
#include <screenInterface.h>
#include <sensorInterfaces.h>
#include <main.h>

//timekeeping variables
uint32_t loop700HzTime = micros();
uint32_t loop700HzPeriodUs = 1428;      //700hz main contol

//stepper motor varialbes
shuttleMotor forMot;
uint8_t const forMotCS       = 19;
uint8_t const forMotSleepPin = 18;
uint8_t const forMotFaultPin = 17;

shuttleMotor bacMot;
uint8_t const bacMotCS       = 36;
uint8_t const bacMotSleepPin = 35;
uint8_t const bacMotFaultPin = 34;

//use the alternative SPI interface pins
uint8_t const spiMosiPin = 0;
uint8_t const spiMisoPin = 1;
uint8_t const spiClkPin  = 32;

//control variables
uint8_t screenLatch = false;
int delayDurMs      = 5000;

/*_________________________________________________________________________*/
/***************************************************************************/

void setup() {
    //start spi interface
    SPI1.begin();

    //init stepper motor actuators
    forMot.init(forMotCS, forMotSleepPin, forMotFaultPin);
    //bacMot.init(bacMotCS, bacMotSleepPin, bacMotFaultPin);

    //init buttons
    initButtonInterfaces();

    //init screen
    initScreen();

    //init serial console
    Serial.begin(BAUDRATE);
    delay(1000);


    Serial.println("initialized shuttle system");

    //reset timers
    loop700HzTime = micros();

    //--------------------
    screenLatch = true;
    dispMsg(String(delayDurMs),2); 
}

/*_________________________________________________________________________*/
/***************************************************************************/

void loop() {

    

    //Motion loop
    if(enableBtSt()&&pauseBtSt()){

        if(screenLatch){
            console("System enabled by enable switch");
            dispMsg("System Enabled",1);
            screenLatch = false;
        }
        forMot.enableMotor(true);
        forMot.moveRightBlocking(delayDurMs);    

        forMot.stopMotor();
        delay(500);

        forMot.moveLeftBlocking(delayDurMs);    

        forMot.stopMotor();
        forMot.enableMotor(false);
        delay(2000);
    }
    else{
        if(!screenLatch){
            console("System locked by enable switch");
            dispMsg("System locked",1);
            screenLatch = true;
        }
        forMot.stopMotor();
        forMot.enableMotor(false);

        //manual motion
        if(!enableBtSt()&&!pauseBtSt()){
            if(upBtSt()&&!downBtSt()){
                forMot.enableMotor(true);
                forMot.moveRightBlocking(500);
                delay(500);    
            } else if (!upBtSt()&&downBtSt()){
                forMot.enableMotor(true);
                forMot.moveLeftBlocking(500);    
                delay(500);    
            }
        }else if(!enableBtSt()&&pauseBtSt()){
            if(upBtSt()&&!downBtSt()){
                delayDurMs += 500;
                dispMsg(String(delayDurMs),2); 
                delay(500);    
            } else if (!upBtSt()&&downBtSt()){
                delayDurMs -= 500;
                if(delayDurMs<0){delayDurMs = 0;}
                dispMsg(String(delayDurMs),2); 
                delay(500);    
            }
        }

        delay(1000);
    }


}
/*_________________________________________________________________________*/
/***************************************************************************/

boolean loop700Hz(){
    if(isTimeUp(loop700HzTime, loop700HzPeriodUs)){
        loop700HzTime = micros();
        return true;
    }
    else{return false;}
}
/*-------------------------------------------------------------------------*/

boolean isTimeUp(uint32_t lastTime, uint32_t periodUs) {
    uint32_t lapsed = 0;;

    if (micros() < lastTime) {
        lapsed = (lastTime - (2 ^ 32)) + micros();
    }
    else {
        lapsed = micros() - lastTime;
    }

    if (lapsed > periodUs) { return true; }
    else { return false; }
}
/*-------------------------------------------------------------------------*/

void console(String msg){
    Serial.println("main: "+msg);
}
/*-------------------------------------------------------------------------*/

/*EOF*/