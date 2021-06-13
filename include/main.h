/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*                              SHUTTLE MOTH                               */
/*-------------------------------------------------------------------------*/
#ifndef main_h
#define main_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <shuttleMotor.h>
#include <buttonInterfaces.h>
#include <screenInterface.h>
#include <sensorInterfaces.h>
#include <main.h>

#define BUFFSIZE 15
#define SERIALTIMEOUT 200
#define BAUDRATE 115200
#define PRINTDEB true

/*_________________________________________________________________________*/
/***************************************************************************/

void setup();
void loop();
boolean loop700Hz();
boolean isTimeUp(uint32_t lastTime, uint32_t periodUs);
void console(String msg);
void enablePwmMotor(boolean enable);
void setPwmMotorSpeed(int speed);

#endif
/*EOF*/