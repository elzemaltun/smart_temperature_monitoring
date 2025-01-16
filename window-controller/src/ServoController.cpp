#include "ServoController.h"
#include <Arduino.h>

ServoController::ServoController(int pin) {
    this->pin = pin;
}

void ServoController::init() {
    servo.attach(pin);                    // Attach servo to specified pin
    Debugger.println("Servo initialized");
    closeWindow();                         // Start with window closed (0%)
}

void ServoController::moveToPercentage(int percentage) {
    // Ensure the percentage is within the valid range (0%–100%)
    percentage = constrain(percentage, 0, 100);
    
    // Map the percentage to PWM values (1000–2000)
    int pwmValue = map(percentage, 0, 100, 1000, 2000);
    
    servo.write(pwmValue);                 // Move the servo to the specified PWM value
    Debugger.print("Moving window to percentage: ");
    Debugger.println(percentage);
}

void ServoController::openWindow() {
    moveToPercentage(100);                  // Open window fully (100%)
}

void ServoController::closeWindow() {
    moveToPercentage(0);                    // Close window fully (0%)
}

void ServoController::update() {
// not needed at the moment 
}
