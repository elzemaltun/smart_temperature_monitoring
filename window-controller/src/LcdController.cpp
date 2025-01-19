#include "LcdController.h"

// Global variables to store previous values
int prevMode = -1;
uint8_t prevPercentage = 255;  // Invalid initial value
float prevTemperature = -999.9; // Invalid initial value

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
    // Only update the display if something has changed
    if (mode != prevMode || percentage != prevPercentage || temperature != prevTemperature) {
        lcd.setCursor(0, 0);
        lcd.print("Mode:        "); // Ensure previous content is overwritten
        lcd.print(mode == 0 ? "AUTO" : "MANUAL");
        lcd.setCursor(0, 1);
        lcd.print("Window:      "); // Ensure previous content is overwritten
        lcd.setCursor(8, 1);
        lcd.print(percentage);
        lcd.print("%");
        lcd.setCursor(0, 2);
        lcd.print("Temp:      "); // Ensure previous content is overwritten
        lcd.setCursor(6, 2);
        lcd.print(temperature, 1);
        lcd.print(" C");

        // Update the previous state to current values
        prevMode = mode;
        prevPercentage = percentage;
        prevTemperature = temperature;
    }
}

void LcdController::lcdPowerOff() {
    lcd.clear();
    lcd.noBacklight(); // Turn off the backlight
}

void LcdController::lcdPowerOn() {
    lcd.backlight(); // Turn on the backlight
}
