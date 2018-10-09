#include "./../header/sensor.h"

Sensor::Sensor()
{
    dht = new DHT(DHTPIN, DHTTYPE);
    this->dht->begin();
}

float Sensor::readHumidity()
{
    return dht->readHumidity();
}

float Sensor::readTemperature()
{
    return dht->readTemperature();
}