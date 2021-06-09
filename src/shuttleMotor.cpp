/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                             SHUTTLE MOTOR                               */
/*-------------------------------------------------------------------------*/

#include <Arduino.h>
#include <SPI.h>
#include <shuttleMotor.h>
#include <main.h>

/*_________________________________________________________________________*/
/***************************************************************************/


void shuttleMotor::init(uint8_t spics, uint8_t sleep, uint8_t fault){
  //define pins for unit
  _spics    = spics;
  _pinsleep = sleep;
  _pinfault = fault;

  //determine pins for sleep and enalbe function
  pinMode(_pinsleep, OUTPUT);
  digitalWrite(_pinsleep, LOW);
  pinMode(_pinfault, INPUT_PULLUP);

  //instantiate the motor driver
  mot = new HighPowerStepperDriver1();
  mot->setChipSelectPin(_spics);

  // Give the driver some time to power up.
  delay(5);

  // Reset the driver to its default settings and clear latched status
  mot->resetSettings();
  mot->clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  mot->setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number in h file
  mot->setCurrentMilliamps36v4(_currentSet);

  // Set the number of microsteps that correspond to one full step.
  mot->setStepMode(HPSDStepMode::MicroStep1);

  // Enable the motor outputs.
  mot->enableDriver();

  //moving flag and timer ISR
  //isrTimer  = new IntervalTimer();
  _ismoving = false;

  if(PRINTDEB){Serial.println("m: init shuttle motor");}
}
/*-------------------------------------------------------------------------*/


void shuttleMotor::moveRight() {
  _ismoving = true;
  mot->setDirection(_direction);
  //isrTimer->begin(stepIsr, _stPeriodUs);  
}   
/*-------------------------------------------------------------------------*/

void shuttleMotor::moveLeft() {
  _ismoving = true;
  mot->setDirection(!_direction);
  //isrTimer->begin(shuttleMotor::stepIsr, _stPeriodUs);  
}
/*-------------------------------------------------------------------------*/

void shuttleMotor::stopMotor() {
  //isrTimer->end();
  _ismoving = false;
}
/*-------------------------------------------------------------------------*/

void shuttleMotor::stepIsr() {
  mot->step();
}
/*-------------------------------------------------------------------------*/

void shuttleMotor::moveRightBlocking(int timeMs) {
  mot->setDirection(_direction);

  uint32_t ttim = millis() + timeMs;

  do {
      mot->step();
      delayMicroseconds(_stPeriodUs);
  } while (millis()<ttim);
}   
/*-------------------------------------------------------------------------*/

void shuttleMotor::moveLeftBlocking(int timeMs) {
  mot->setDirection(!_direction);

  uint32_t ttim = millis() + timeMs;

  do {
      mot->step();
      delayMicroseconds(_stPeriodUs);
  } while (millis() < ttim);
}
/*-------------------------------------------------------------------------*/


void shuttleMotor::enableMotor(boolean enable) {
  if(enable){digitalWrite(_pinsleep, HIGH);}
  else{digitalWrite(_pinsleep, LOW);}
}
/*-------------------------------------------------------------------------*/


boolean shuttleMotor::isFault() {
  return digitalRead(_pinfault);
}
/*-------------------------------------------------------------------------*/


void shuttleMotor::motorSpeed(int speed) {
  if(speed<0){
    speed = 0;
    }
  else if(speed>100){
      speed = 100;
    }

  _stPeriodUs = floor((_stPeriodUsMax-_stPeriodUsMin)*(speed/100))+_stPeriodUsMin;
}
/*-------------------------------------------------------------------------*/

/*EOF*/
