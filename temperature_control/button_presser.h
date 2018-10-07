#ifndef BUTTON_PRESSER_H
#define BUTTON_PRESSER_H
#include <Servo.h>
#include <cmath>
#include "utils.h"
#define SERVO_PIN 0 // D3 on NodeMCU
#define SERVO_DECREASE_ANGLE 0
#define SERVO_NEUTRAL_ANGLE 90
#define SERVO_INCREASE_ANGLE 180
#define DECREASE 0
#define INCREASE 1

class ButtonPresser
{
private:
  Servo servo;
  byte currentServoAngle;
  /// The temperature that the thermostat has as its target temperature
  /// [thermostatTargetTemp] will be set to be equal to [targetTemp] from class [App]
  float thermostatTargetTemp;

public:
  ButtonPresser();
  void init();
  /// This function presses the buttons on the thermostat
  void update(float);
  float getThermostatTargetTemp() { return thermostatTargetTemp; }

private:
  void setServo(byte);
  float readThermostatTargetTemp();
  void writeThermostatTargetTemp();
};

#endif
