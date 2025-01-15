#ifndef TEMPSSENSOR_H
#define TEMPSSENSOR_H

#include <Arduino.h>

class TempSensor {
private:
    uint8_t pin;           // Analog pin for the temperature sensor
    float voltageRef;      // Reference voltage for the ADC

public:
    // Constructor
    TempSensor(uint8_t analogPin, float refVoltage = 3.3);

    // Method to read temperature in Celsius
    float readTemperatureC();

};

#endif 