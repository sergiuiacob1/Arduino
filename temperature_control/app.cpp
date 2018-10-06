#include <Arduino.h>
#include "app.h"
#include "api.h"
#define BAUD_RATE 115200

App::App()
{
}

void App::init()
{
    Serial.begin(BAUD_RATE);
    Serial.println("Hello!");
    this->connectToWifi();
}

void App::connectToWifi()
{
    Serial.print("Connecting to " + SSID_NAME);
    WiFi.begin(SSID_NAME, SSID_PWD);
    Serial.println("Trying to connect to Wifi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("Connected to " + SSID_NAME);
    Serial.println("");
}