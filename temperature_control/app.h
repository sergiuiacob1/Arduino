#ifndef APP_H
#define APP_H
#include "ESP8266WiFi.h"
#include "api.h"
#include "sensor.h"
#include "button_presser.h"
#include <EEPROM.h>
#include <Arduino.h>

/// The main project
/// I control everything using this class
class App
{
  private:
    Sensor sensor;
    Api api;
    ButtonPresser buttonPresser;
    /// The temperature that I wish to be in the room
    byte targetTemp;

  public:
    App();
    void init();
    float readHumidity() { return sensor.readHumidity(); }
    float readTemperature() { return sensor.readTemperature(); }
    void postData();
    void update();

  private:
    void connectToWifi();
};

#endif
