#include "./../header/app.h"
#define BAUD_RATE 115200

App::App()
{
    targetTemp = 22; // set a default of 22*C in case Arduino can't connect to the network
    _lastAppPost = APP_POST_INTERVAL;
    _lastAppUpdate = APP_UPDATE_INTERVAL;
}

void App::init()
{
    Serial.begin(BAUD_RATE);
    this->connectToWifi();
    buttonPresser.init();
    display.init();
    display.showOnDisplay(buttonPresser.getThermostatTargetTemp());
}

void App::connectToWifi()
{
    Serial.println("Connecting to Wifi: " + (String)SSID_NAME + "...");
    WiFi.begin(SSID_NAME, SSID_PWD);
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
    if (millis() - _lastAppPost < APP_POST_INTERVAL)
        return;

    Serial.println("Posting data...");
    float humidity = sensor.readHumidity();
    float temperature = sensor.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        _lastAppPost = millis(); // even if it fails, don't try to read again immediately
        return;
    }
    if (api.postData(humidity, temperature, buttonPresser.getThermostatTargetTemp()))
        Serial.println("Posted data successfully!");
    else
        Serial.println("There was an error during data post: " + api.getErrorMessage());

    _lastAppPost = millis();
    Serial.println("Done posting data.");
    Serial.println("");
}

void App::update()
{
    if (millis() - _lastAppUpdate < APP_UPDATE_INTERVAL)
        return;

    Serial.println("Updating app...");
    // retrieve the target temperature using the api
    if (api.getTargetTemp(targetTemp) == false)
    {
        Serial.println("Error during GET targetTemp: " + api.getErrorMessage());
        return;
    }
    Serial.println("Target temperature: " + (String)targetTemp);
    buttonPresser.update(targetTemp, display);
    showOnDisplay(buttonPresser.getThermostatTargetTemp());

    _lastAppUpdate = millis();
    Serial.println("Done updating app.");
    Serial.println("");
}

void App::showOnDisplay(float value)
{
    display.showOnDisplay(value);
}