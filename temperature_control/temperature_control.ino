#include "app.h"

App app;

void setup()
{
  app.init();
}

void loop()
{
  if (app.isConnectedToWifi() == false) // in case the ESP8266 disconnected
  {
    app.connectToWifi();
    return;
  }
  app.update();   // check if target temperature modified
  app.postData(); // post the room humidity and temperature to thingspeak
  return;
}
