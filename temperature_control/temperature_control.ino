#include "app.h"

App app;

void setup()
{
  app.init();
}

void loop()
{
  if (app.isConnectedToWifi() == false)
  {
    app.connectToWifi();
    return;
  }
  app.update();   // check if target temperature modified
  app.postData(); // post the room humidity and temperature to thingspeak
  return;
}
