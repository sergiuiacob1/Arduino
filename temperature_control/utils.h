#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include <EEPROM.h>

template <class T>
int EEPROM_writeAnything(int, const T &);
template <class T>
int EEPROM_readAnything(int, T &);
#endif