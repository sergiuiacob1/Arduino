#include "app.h"
#define BAUD_RATE 115200

App::App()
{
    targetTemp = 22; // set a default of 22*C in case Arduino can't connect to the network
}

void App::init()
{
    Serial.begin(BAUD_RATE);
    this->connectToWifi();
    buttonPresser.init();
}

void App::connectToWifi()
{
    Serial.println("Connecting to Wifi...");
    Serial.print("Connecting to " + *SSID_NAME);
    WiFi.begin(SSID_NAME, SSID_PWD);
    Serial.println("Trying to connect to Wifi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("Connected to " + *SSID_NAME);
    Serial.println("Done connecting to Wifi.");
    Serial.println("");
}

void App::postData()
{
    Serial.println("Posting data...");
    float humidity = sensor.readHumidity();
    float temperature = sensor.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    if (api.postData(humidity, temperature))
        Serial.println("Posted data successfully!");
    else
        Serial.println("There was an error during data post: " + api.getErrorMessage());
    Serial.println("Done posting data.");
    Serial.println("");
}

void App::update()
{
    Serial.println("Updating app...");
    // retrieve the target temperature using the api
    if (api.getTargetTemp(targetTemp) == false)
    {
        Serial.println("Error during GET targetTemp: " + api.getErrorMessage());
        return;
    }
    Serial.println("Target temperature: " + (String)targetTemp);
    buttonPresser.update(targetTemp);

    Serial.println("Done updating app.");
    Serial.println("");
}