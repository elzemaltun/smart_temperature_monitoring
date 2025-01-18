#include "SerialCommTask.h"
#include "Debug.h"
#include <Arduino.h>

SerialCommTask::SerialCommTask(WindowControlTask* windowControlTask) {
    this->windowControlTask = windowControlTask;
    this->ackMessage = "";
    this->windowOpeningLevel = 0;
    this->mode = AUTOMATIC; // Default mode
}

void SerialCommTask::init(int period) {
    Task::init(period);  // Call base class init
    Serial.begin(9600);  // Initialize Serial communication
}

void SerialCommTask::tick() {
    readSerial();
}

void SerialCommTask::readSerial() {
    while (Serial.available() > 0) {
        String message = Serial.readStringUntil('\n');
        parseMessage(message);
    }
}

void SerialCommTask::parseMessage(String message) {
    if (message.startsWith("{REQ")) {
        handleRequestMessage(message);
    } else {
       // sendErrorMessage();
    }
}

void SerialCommTask::handleRequestMessage(String message) {
    // Parse and handle request message
    Debugger.println("Handling request message: " + message);
    
    int modeReceived = message.charAt(5) - '0';  // Extract mode (0 or 1)
    int windowLevelReceived = message.charAt(7) - '0';  // Extract window opening level (0-100)

    // If mode changes, update mode and window control task
    if (modeReceived != mode) {
        mode = modeReceived;
        windowControlTask->setMode(static_cast<Mode>(mode));  // Set the new mode
    }

    // If mode is manual, update window level
    if (mode == MANUAL) {
        windowOpeningLevel = windowLevelReceived;
        //windowControlTask->setWindowLevel(windowOpeningLevel);  // Set the window level
    }

    sendStatusMessage();
}

void SerialCommTask::sendStatusMessage() {
    // Sending back the acknowledgment message in the required format
    String statusMessage = "{ACK, " + String(windowOpeningLevel) + ", " + String(25.0) + ", " + String(mode) + "}";  // Placeholder temperature
    Serial.println(statusMessage);
}

void SerialCommTask::sendErrorMessage() {
    Serial.println("ERROR: Invalid Command");
}
