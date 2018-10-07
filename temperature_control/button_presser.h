#ifndef BUTTON_PRESSER_H
#define BUTTON_PRESSER_H
#include <Arduino.h>
#include <Servo.h>
#define SERVO_PIN 4 // D2 on NodeMCU
#define SERVO_DECREASE_ANGLE 45
#define SERVO_INCREASE_ANGLE 135

class ButtonPresser
{
private:
  Servo servo;
  byte currentServoAngle;
  /// The temperature that the thermostat has as its target temperature
  /// [thermostatTargetTemp] will be set to be equal to [targetTemp] from class [App]
  byte thermostatTargetTemp;

public:
  ButtonPresser();
  void init();
  void update(byte);

private:
  void setServo(byte);
};

#endif
