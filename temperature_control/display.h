#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include "TM1637Display.h"
#define CLK 5 // D1 on nodeMCU
#define DIO 4 // D2 on nodeMCU

class Display
{
  private:
    TM1637Display *display;

  public:
    Display();
    void init();
    void showOnDisplay(float);
};

#endif