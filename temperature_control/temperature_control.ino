#include "app.h"

App app;

void setup()
{
  app.init();
}

void loop()
{
  app.update();   // check if target temperature modified
  app.postData(); // post the room humidity and temperature to thingspeak
  delay(10000);   // post data every minute
  // sa schimb asta!!!
  //update-ul trebuie sa fie asincron fata de postdata!!!!
  return;
}
