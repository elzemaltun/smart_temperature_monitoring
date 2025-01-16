#include "SerialCommTask.h"
#include "Debug.h"

SerialCommTask::SerialCommTask(WindowControlTask* windowControlTask) {
    this->windowControlTask = windowControlTask;
    this->ackMessage = "";
    this->windowOpeningLevel = 0;
    this->mode = 0;
}

void SerialCommTask::init() {
    Serial.begin(9600);
}

void SerialCommTask::tick() {
    if (Serial.available() > 0) {
        String message = Serial.readStringUntil('\n');
        parseMessage(message);
    }
}

void SerialCommTask::parseMessage(String message) {
    // Remove any extra spaces or invalid characters
    message.trim();

    if (message.startsWith("{REQ")) {
        handleRequestMessage(message);
    } else {
        sendErrorMessage();
    }
}

void SerialCommTask::handleRequestMessage(String message) {
    int modeIndex = message.indexOf("MODE");
    int levelIndex = message.indexOf("WINDOW_OPENING_LEVEL");

    if (modeIndex != -1 && levelIndex != -1) {
        mode = message.substring(modeIndex + 5, modeIndex + 6).toInt();
        windowOpeningLevel = message.substring(levelIndex + 22).toInt();

        if (mode == 0) {
            windowControlTask->switchToAutomaticMode(windowOpeningLevel);
        } else if (mode == 1) {
            windowControlTask->switchToManualMode(windowOpeningLevel);
        }

        sendStatusMessage();
    } else {
        sendErrorMessage();
    }
}

void SerialCommTask::sendStatusMessage() {
    int currentMode = windowControlTask->getMode();
    int currentWindowPercentage = windowControlTask->getWindowPercentage();
    float currentTemperature = windowControlTask->getTemperature();

    ackMessage = "{ACK, " + String(currentWindowPercentage) + ", " + String(currentTemperature, 1) + ", " + String(currentMode) + "}";
    Serial.println(ackMessage);
}

void SerialCommTask::sendErrorMessage() {
    ackMessage = "{ERROR}";
    Serial.println(ackMessage);
}
