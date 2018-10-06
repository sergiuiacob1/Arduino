#ifndef APP_H
#define APP_H
#include "ESP8266WiFi.h"
#include "credentials.h"

class App
{
  public:
    App();
    void init();

  private:
    void connectToWifi();
};

#endif