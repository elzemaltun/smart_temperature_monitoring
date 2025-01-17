#include "LcdController.h"

LcdController::LcdController(uint8_t address, uint8_t cols, uint8_t rows)
    : lcd(address, cols, rows), lcdCols(cols), lcdRows(rows) {}

void LcdController::init() {
    lcd.init();
    lcd.begin(lcdCols, lcdRows); // Correctly specify dimensions
    lcd.backlight();
}

void LcdController::displayMode(const char* mode) {
    lcd.setCursor(0, 0); // First line, left side
    lcd.print("Mode: ");
    lcd.print(mode);
}

void LcdController::displayWindowPercentage(uint8_t percentage) {
    int position = lcdCols / 2 - 4; // Middle of the second line for the percentage
    lcd.setCursor(position, 1); // Second line, starting from the middle
    lcd.print("Window: ");
    lcd.print(percentage);
    lcd.print("%");
}

void LcdController::displayTemperature(float temperature) {
    lcd.setCursor(0, 1); // Second line, left side
    lcd.print("Temp: ");
    lcd.print(temperature, 1); // 1 decimal place for temperature
    lcd.print(" C");
}

void LcdController::updateDisplay(const char* mode, uint8_t percentage, float temperature) {
    lcd.clear();
    displayMode(mode);
    if (strcmp(mode, "MANUAL") == 0) {
        displayTemperature(temperature);
    }
    displayWindowPercentage(percentage);
}

/* combined function that should display everything together */
void LcdController::displayStatus(uint8_t percentage, float temperature, int mode) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mode: ");
    lcd.print(mode == 0 ? "AUTO" : "MANUAL");
    lcd.setCursor(0, 1);
    lcd.print("Window: ");
    lcd.print(percentage);
    lcd.print("%");
    lcd.print(" Temp: ");
    lcd.print(temperature, 1);
    lcd.print(" C");
}


void LcdController::lcdPowerOff() {
    lcd.clear();
    lcd.noBacklight(); // Turn off the backlight
}

void LcdController::lcdPowerOn() {
    lcd.backlight(); // Turn on the backlight
}
