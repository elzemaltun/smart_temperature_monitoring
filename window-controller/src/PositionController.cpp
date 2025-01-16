#include "PositionController.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
}

void Potentiometer::init() {
    pinMode(pin, INPUT);
}

int Potentiometer::getPercentage() {
    int rawValue = analogRead(pin); // Read the raw analog value (0–1023)
    return map(rawValue, 0, 1023, 0, 100); // Map to a percentage (0–100)
}
