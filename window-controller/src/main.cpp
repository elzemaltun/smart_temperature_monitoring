#include <Arduino.h>
#include "Scheduler.h"
#include "WindowControlTask.h"
#include "SerialCommTask.h"
#include "Debug.h"
#include "Button.h"
#include "LcdController.h"
#include "ServoController.h"
#include "PositionController.h"

// Scheduler and Tasks
Scheduler sched;
WindowControlTask* windowControlTask;
SerialCommTask* serialCommTask;

/*
 * Pin Connections used:
 * 
 * Button              | D2
 * Servo Motor         | D9 (PWM)
 * Potentiometer       | A0
 * I2C LCD (SDA)       | A4
 * I2C LCD (SCL)       | A5
 */


// Hardware components
Button button(2);  // Button connected to pin 2
LcdController lcd(0x27, 16, 2);  // I2C address, 16x2 LCD
ServoController servo(9);  // Servo connected to pin 9
PositionController potentiometer(A0);  // Potentiometer connected to analog pin A0

void setup() {
    // Initialize debug output
    Debugger.begin(9600);
    Serial.begin(9600);
    Debugger.println("Window Control System Initializing...");

    // Initialize scheduler
    sched.init(50);  // 50ms base period

    // Create and initialize WindowControlTask
    windowControlTask = new WindowControlTask(&button, &lcd, &servo, &potentiometer);
    windowControlTask->init(100);  // 100ms task period
    sched.addTask(windowControlTask);

    // Create and initialize SerialCommTask
    serialCommTask = new SerialCommTask(windowControlTask);
    serialCommTask->init(100);  // 100ms task period
    sched.addTask(serialCommTask);

    Debugger.println("System Setup Complete.");
}

void loop() {
    serialCommTask->readSerial();  // Handle incoming serial communication
    sched.schedule();  // Execute scheduled tasks
}
