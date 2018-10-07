#include "button_presser.h"

ButtonPresser::ButtonPresser()
{
    currentServoAngle = 90;
    thermostatTargetTemp = 20; // asta o sa trebuiasca scris in EEPROM
}

void ButtonPresser::init()
{
    // set the microservo in neutral position
    servo.attach(SERVO_PIN);
    Serial.println("Puting servo in neutral position");
    setServo(90);
}

void ButtonPresser::update(byte targetTemp)
{
    setServo(targetTemp);
}

void ButtonPresser::setServo(byte angle)
{
    int i;
    if (angle == currentServoAngle)
        return;

    Serial.println("Setting servo to angle: " + (String)angle);

    if (angle < currentServoAngle)
    {
        for (i = currentServoAngle; i >= angle; --i)
        {
            servo.write(i);
            delay(10);
        }
    }
    else
    {
        for (i = currentServoAngle; i <= angle; ++i)
        {
            servo.write(i);
            delay(10);
        }
    }
    currentServoAngle = angle;
}