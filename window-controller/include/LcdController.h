#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Debug.h"

class LcdController {
private:
    LiquidCrystal_I2C lcd;
    uint8_t lcdCols;
    uint8_t lcdRows;

public:
    LcdController(uint8_t address, uint8_t cols, uint8_t rows);
    void init();
    void displayMode(const char* mode);
    void displayWindowPercentage(uint8_t percentage);
    void displayTemperature(float temperature);
    void updateDisplay(const char* mode, uint8_t percentage, float temperature);
    void lcdPowerOff();
    void lcdPowerOn();
    void displayStatus(uint8_t percentage, float temperature, int mode);

};

#endif // LCDCONTROLLER_H
