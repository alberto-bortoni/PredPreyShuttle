/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                             SHUTTLE MOTOR                               */
/*-------------------------------------------------------------------------*/
#ifndef shuttleMot_h
#define shuttleMot_h

#include <Arduino.h>
#include <SPI.h>
#include <HighPowerStepperDriver1.h>
#include <main.h>

/*_________________________________________________________________________*/
/***************************************************************************/
class shuttleMotor
{
  public:
    void init(uint8_t spics, uint8_t sleep, uint8_t fault);
    void moveRight();
    void moveLeft();
    void stopMotor();
    void moveRightBlocking(int timeMs);
    void moveLeftBlocking(int timeMs);
    void enableMotor(boolean enable); 
    boolean isFault();
    void motorSpeed(int speed);
    void stepIsr();
    int getMotorSpeed(void);
  private:
    uint8_t _spics;
    uint8_t _pinsleep;
    uint8_t _pinfault;
    uint8_t _ismoving;
    IntervalTimer *isrTimer;
    HighPowerStepperDriver1 *mot;
    bool _direction       = true; //change to false if rotating is opposite
    uint32_t _stepsPerRev      = 200;  //from motor datasheet
    uint32_t _currentSet       = 2000; //1500;
    const uint32_t _maxCurrent = 2000; // 2000; //from datasheet
    uint32_t _stepIncrementUs  = 2;
    uint32_t _stPeriodUs       = 1500;
    uint32_t _stPeriodUsMin    = 460;
    uint32_t _stPeriodUsMax    = 1500;
};
#endif
/*-------------------------------------------------------------------------*/
/*EOF*/
