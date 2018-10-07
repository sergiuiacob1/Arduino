#ifndef SENSOR_H
#define SENSOR_H
#include "DHT.h"
#define DHTPIN 2 //D4 on esp board
#define DHTTYPE DHT11

/// Represents a DHT sensor, used to read temperature and humidity
class Sensor
{
  private:
    DHT *dht;

  public:
    Sensor();
    float readTemperature();
    float readHumidity();
};

#endif