#include "button_presser.h"

ButtonPresser::ButtonPresser()
{
}

void ButtonPresser::init()
{
    EEPROM.begin(512); // initialize EEPROM
    servo.attach(SERVO_PIN);
    currentServoAngle = (byte)servo.read();
    setServo(SERVO_NEUTRAL_ANGLE);                     // put servo in neutral position
    thermostatTargetTemp = readThermostatTargetTemp(); // DE MODIFICAT
}

void ButtonPresser::update(float targetTemp, Display &display)
{
    Serial.println("Thermostat is set to: " + (String)thermostatTargetTemp);
    byte direction, steps;
    if (targetTemp == thermostatTargetTemp)
        return;

    if (targetTemp > thermostatTargetTemp)
        direction = INCREASE; // I have to press the increase button on the thermostat
    else
        direction = DECREASE; // I have to press the decrease button on the thermostat

    // a press changes the temperature by 0,5 degrees
    steps = (byte)(fabs(targetTemp - thermostatTargetTemp) / 0.5); // how many times I have to press the button
    steps += 1;                                                    // I need to take an extra step to activate the temperature changing mode on my thermostat

    for (int i = 0; i < steps; ++i)
    {
        setServo(SERVO_NEUTRAL_ANGLE);
        if (direction == DECREASE)
        {
            setServo(SERVO_DECREASE_ANGLE);
            if (i > 0) // the first step is just to activate the thermostat
                thermostatTargetTemp -= 0.5;
        }
        else
        {
            setServo(SERVO_INCREASE_ANGLE);
            if (i > 0) // the first step is just to activate the thermostat
                thermostatTargetTemp += 0.5;
        }
        if (i > 0)
        {
            writeThermostatTargetTemp();
            display.showOnDisplay(thermostatTargetTemp);
        }
    }

    setServo(SERVO_NEUTRAL_ANGLE);
}

void ButtonPresser::setServo(byte angle)
{
    int i;
    // Switching "on" the servo
    pinMode(SERVO_PIN, OUTPUT);
    Serial.println("Setting servo to angle: " + (String)angle);
    servo.write(angle);
    delay(1000); // give servo time to move;
    currentServoAngle = angle;
    // Switching "off" the servo to avoid buzzing
    pinMode(SERVO_PIN, INPUT);
}

float ButtonPresser::readThermostatTargetTemp()
{
    float result;
    Serial.println("Reading from EEPROM...");
    EEPROM_readAnything(0, result);
    Serial.println("Read the value: " + (String)result);
    Serial.println("Done reading from EEPROM.");
    return result;
}

void ButtonPresser::writeThermostatTargetTemp()
{
    Serial.println("Writing into EEPROM...");
    EEPROM_writeAnything(0, thermostatTargetTemp);
    Serial.println("Done writing into EEPROM");
}