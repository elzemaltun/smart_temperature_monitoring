#include "WindowControlTask.h"
#include "Debug.h"
#include "LcdController.h"
#include "ServoController.h"
#include "Button.h"
#include "PositionController.h"

WindowControlTask::WindowControlTask(Button* button, LcdController* lcd, ServoController* servo, PositionController* potentiometer) {
    this->button = button;
    this->lcd = lcd;
    this->servo = servo;
    this->potentiometer = potentiometer;
    this->mode = 0; // Default to AUTOMATIC mode
    this->windowPercentage = 0;
    this->temperature = 25.0; // Placeholder temperature
}

void WindowControlTask::init() {
    button->init();
    servo->init();
    potentiometer->init();
    lcd->init();
}

void WindowControlTask::tick() {
    switch (mode) {
        case 0: // AUTOMATIC Mode
            handleAutomaticMode();
            break;
        case 1: // MANUAL Mode
            handleManualMode();
            break;
    }
}

void WindowControlTask::handleAutomaticMode() {
    // Here you would receive the window opening level from the control unit (via serial communication)
    // For now, simulate with a placeholder value (e.g., 50%)
    windowPercentage = 50;  // Placeholder for received level
    
    servo->moveToPercentage(windowPercentage);
    lcd->displayStatus(windowPercentage, temperature, mode);

    if (button->isPressed()) {
        mode = 1; // Switch to MANUAL mode
        Debugger.println("Switching to MANUAL mode.");
    }
}

void WindowControlTask::handleManualMode() {
    // Read potentiometer value to determine window opening percentage
    windowPercentage = potentiometer->getPercentage();
    servo->moveToPercentage(windowPercentage);
    lcd->displayStatus(windowPercentage, temperature, mode);

    if (button->isPressed()) {
        mode = 0; // Switch to AUTOMATIC mode
        Debugger.println("Switching to AUTOMATIC mode.");
    }
}
