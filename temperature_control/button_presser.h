#ifndef BUTTON_PRESSER_H
#define BUTTON_PRESSER_H
#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#define SERVO_PIN 4 // D2 on NodeMCU
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

private:
  void setServo(byte);
  byte readThermostatTargetTemp();
  void writeThermostatTargetTemp();
};

#endif
