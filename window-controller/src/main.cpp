#include <Arduino.h>
#include "WindowControlTask.h"
#include "SerialCommTask.h"
#include "Button.h"
#include "LcdController.h"
#include "ServoController.h"
#include "PositionController.h"

Button button(2);
LcdController lcd(0x27, 16, 2);  // I2C address, 16x2 LCD
ServoController servo(9);
PositionController potentiometer(A0);

WindowControlTask windowControlTask(&button, &lcd, &servo, &potentiometer);
SerialCommTask serialCommTask(&windowControlTask);

void setup() {
    windowControlTask.init();
    serialCommTask.init();
}

void loop() {
    windowControlTask.tick();
    serialCommTask.tick();
}
