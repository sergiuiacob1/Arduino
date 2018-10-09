#include "./../header/display.h"

Display::Display()
{
    display = new TM1637Display(CLK, DIO);
}

void Display::init()
{
    pinMode(CLK, OUTPUT);
    pinMode(DIO, OUTPUT);
    Serial.println("Initializing display...");
    display->setBrightness(0x0f);
    Serial.println("Done initializing display.");
}

void Display::showOnDisplay(float value)
{
    int toShow = value * 10;
    Serial.println("Showing on display: " + (String)toShow);
    display->showNumberDec(toShow);
}