#include "Button.h"

Button::Button(int pin) {
    this->pin = pin;
}

void Button::init() {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    // Directly read the button state since we will be running it as a task. no debounce needed
    return digitalRead(pin) == LOW; // Assuming LOW means pressed
}
