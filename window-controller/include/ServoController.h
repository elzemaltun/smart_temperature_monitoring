#ifndef __SERVOCONTROLLER__
#define __SERVOCONTROLLER__

#include "ServoTimer2.h"  
#include "Debug.h"

class ServoController {
public:
    ServoController(int pin);               // Constructor to initialize servo with pin
    void init();                            // Initialize the servo
    void moveToPercentage(int percentage);  // Move servo to a specific percentage (0%–100%)
    void openWindow();                      // Open window fully (100%) --> can be used at start etc 
    void closeWindow();                     // Close window fully (0%)
    void update();                          // Update function for other tasks (if needed)

private:
    int pin;                                // Pin for the servo motor
    ServoTimer2 servo;                      // Servo motor object
};

#endif
