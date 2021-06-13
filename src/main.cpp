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

//stepper motor varialbes
shuttleMotor forMot;
uint8_t const forMotCS       = 19;
uint8_t const forMotSleepPin = 18;
uint8_t const forMotFaultPin = 17;

//use the alternative SPI interface pins
uint8_t const spiMosiPin = 0;
uint8_t const spiMisoPin = 1;
uint8_t const spiClkPin  = 32;

//control variables
uint8_t screenLatch = false;
int delayDurMs      = 5000;
int setSpeed        = 50;

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


    console("initialized shuttle system");

    //reset timers
    loop700HzTime = micros();

    //--------------------
    screenLatch = true;

    forMot.stopMotor();
    forMot.enableMotor(false);
    forMot.motorSpeed(setSpeed);

    dispMsg("Initialized", 1);
    dispMsg(speedAndDelay(setSpeed, delayDurMs),2); 

    delay(1000);
}

/*_________________________________________________________________________*/
/***************************************************************************/

void loop() {

    //perform normal loop
    if(enableBtSt()&&pauseBtSt()){

        if(screenLatch){
            console("System enabled by enable switch");
            dispMsg("System Enabled",1);
            screenLatch = false;
        }
       
        //moveRight
        forMot.enableMotor(true);
        delay(50);
        forMot.moveRightBlocking(delayDurMs);

        //move left 
        forMot.stopMotor();
        delay(100);
        forMot.moveLeftBlocking(delayDurMs);
        
        //stop
        forMot.stopMotor();
        forMot.enableMotor(false);
        delay(500);
    }
    else{
        if(!screenLatch){
            console("System locked by enable switch");
            dispMsg("System locked",1);
            screenLatch = true;
        }

        //adjust motor speed
        if(!enableBtSt()&&!pauseBtSt()){
            if(upBtSt()&&!downBtSt()){
                setSpeed += 5;
                if (setSpeed >= 100){setSpeed = 100;}
                forMot.motorSpeed(setSpeed);
                dispMsg(speedAndDelay(setSpeed, delayDurMs),2); 
            } else if (!upBtSt()&&downBtSt()){
                setSpeed -= 5;
                if (setSpeed <= 0){setSpeed = 0;}
                forMot.motorSpeed(setSpeed);
                dispMsg(speedAndDelay(setSpeed, delayDurMs),2); 
            }
        //adjust motor delay
        } else if(!enableBtSt()&&pauseBtSt()){
            if(upBtSt()&&!downBtSt()){
                delayDurMs += 100;
                if (delayDurMs >= 10000){delayDurMs = 10000;}
                dispMsg(speedAndDelay(setSpeed, delayDurMs),2); 
            } else if (!upBtSt()&&downBtSt()){
                delayDurMs -= 100;
                if (delayDurMs <=0){delayDurMs = 0;}
                dispMsg(speedAndDelay(setSpeed, delayDurMs),2); 
            }
        }
        delay(100);
    }

}
/*_________________________________________________________________________*/
/***************************************************************************/

boolean loop700Hz(){
    static const uint32_t loopPeriod = floor(1000000/700);
    if(isTimeUp(loop700HzTime, loopPeriod)){
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