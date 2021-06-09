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
  private:
    uint8_t _spics;
    uint8_t _pinsleep;
    uint8_t _pinfault;
    uint8_t _ismoving;
    IntervalTimer *isrTimer;
    HighPowerStepperDriver1 *mot;
    bool _direction       = true; //change to false if rotating is opposite
    int _stepsPerRev      = 200; //from motor datasheet
    int _currentSet       = 1000; //1500;
    const int _maxCurrent = 1500;// 2000; //from datasheet
    int _stPeriodUs       = 1500;
    int _stPeriodUsMin    = 1500;
    int _stPeriodUsMax    = 4500;
};
#endif
/*-------------------------------------------------------------------------*/
/*EOF*/
