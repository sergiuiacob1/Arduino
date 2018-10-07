#ifndef APP_H
#define APP_H
#include "ESP8266WiFi.h"
#include "api.h"
#include "sensor.h"
#include "button_presser.h"
#include <EEPROM.h>
#include <Arduino.h>
#define APP_UPDATE_INTERVAL 10000 // update every 10 seconds
#define APP_POST_INTERVAL 120000   // post data every 2 minutes

/// The main project
/// I control everything using this class
class App
{
  private:
    Sensor sensor;
    Api api;
    ButtonPresser buttonPresser;
    /// The temperature that I wish to be in the room
    float targetTemp;
    unsigned long long int _lastAppUpdate, _lastAppPost;

  public:
    App();
    void init();
    void postData();
    void update();

    void test()
    {
        buttonPresser.update(SERVO_DECREASE_ANGLE);
        delay(3000);
        buttonPresser.update(90);
        delay(3000);
        buttonPresser.update(SERVO_INCREASE_ANGLE);
    }

  private:
    void connectToWifi();
    float readHumidity() { return sensor.readHumidity(); }
    float readTemperature() { return sensor.readTemperature(); }
};

#endif
