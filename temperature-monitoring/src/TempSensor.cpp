#include "TempSensor.h"

// Constructor
TempSensor::TempSensor(uint8_t analogPin, float refVoltage) {
    pin = analogPin;
    pinMode(pin, INPUT);
}

// Read temperature in Celsius and check against the threshold
float TempSensor::readTemperatureC() {
    int raw = analogRead(pin); // Read raw ADC value
    float voltage = (raw * voltageRef) / 1024.0; // Convert ADC value to voltage
    float temperatureC = (voltage - 0.5) * 100.0; // TMP36 conversion formula

    return temperatureC;
}
