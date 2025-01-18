#include "WindowControlTask.h"
#include "Debug.h"

WindowControlTask::WindowControlTask(Button* button, LcdController* lcd, ServoController* servo, PositionController* potentiometer) {
    this->button = button;
    this->lcd = lcd;
    this->servo = servo;
    this->potentiometer = potentiometer;
    this->mode = AUTOMATIC;     // Default to AUTOMATIC mode
    this->windowPercentage = 0;
    this->temperature = 25.0;   // Placeholder temperature
}

void WindowControlTask::init(int period) {
    Task::init(period);  // Call base class init
    button->init();
    servo->init();
    potentiometer->init();
    lcd->init();
}

void WindowControlTask::tick() {
    switch (mode) {
        case AUTOMATIC:
            handleAutomaticMode();
            break;
        case MANUAL:
            handleManualMode();
            break;
    }
}

void WindowControlTask::handleAutomaticMode() {
    windowPercentage = 50;  // Placeholder for received level
    // servo->moveToPercentage(windowPercentage);
    lcd->displayStatus(windowPercentage, temperature, mode);

    if (button->isPressed()) {
        mode = MANUAL; // Switch to MANUAL mode
        Debugger.println("Switching to MANUAL mode.");
    }
}

void WindowControlTask::handleManualMode() {
    windowPercentage = potentiometer->getPercentage();
    servo->moveToPercentage(windowPercentage);
    lcd->displayStatus(windowPercentage, temperature, mode);

    if (button->isPressed()) {
        mode = AUTOMATIC; // Switch to AUTOMATIC mode
        Debugger.println("Switching to AUTOMATIC mode.");
    }
}

void WindowControlTask::setMode(Mode newMode) {
    mode = newMode;
    Debugger.println("Mode set to: " + String(mode == AUTOMATIC ? "AUTOMATIC" : "MANUAL"));
}

void WindowControlTask::setWindowLevel(int level) {
    if (mode == MANUAL) {
        windowPercentage = level;
        servo->moveToPercentage(windowPercentage);  // Move the servo to the new level
        Debugger.println("Window level set to: " + String(windowPercentage));
    }
}
