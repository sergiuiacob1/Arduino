#ifndef API_H
#define API_H
#include "credentials.h"
#include "ESP8266WiFi.h"
#include <ArduinoHttpClient.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#define MAX_RESPONSE_SIZE 4096
#define GET_NO_RESULTS 5

class Api
{
  private:
    WiFiClient wifi;
    String errorMessage;

  public:
    Api();
    bool postData(float, float);
    String getErrorMessage() { return errorMessage; }
    bool getTargetTemp(float &);
};

#endif