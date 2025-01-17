#include "PositionController.h"

PositionController::PositionController(int pin) {
    this->pin = pin;
}

void PositionController::init() {
    pinMode(pin, INPUT);
}

int PositionController::getPercentage() {
    int value = analogRead(pin);
    return map(value, 0, 1010, 0, 100); // Maps the analog value to a percentage (0-100) - value of analog adjusted to get full 100%
}
