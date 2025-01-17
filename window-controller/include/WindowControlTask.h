#ifndef __WINDOWCONTROLTASK__
#define __WINDOWCONTROLTASK__

#include "Task.h"
#include "Button.h"
#include "LcdController.h"
#include "ServoController.h"
#include "PositionController.h"

enum Mode {
    AUTOMATIC = 0,
    MANUAL = 1
};

class WindowControlTask : public Task {
private:
    Button* button;
    LcdController* lcd;
    ServoController* servo;
    PositionController* potentiometer;
    Mode mode;  // 0 = AUTOMATIC, 1 = MANUAL
    uint8_t windowPercentage;
    float temperature;

    void handleAutomaticMode();
    void handleManualMode();

public:
    WindowControlTask(Button* button, LcdController* lcd, ServoController* servo, PositionController* potentiometer);
    void init(int period) override; // Inherit from Task
    void tick() override;          // Inherit from Task
    void setMode(Mode newMode);    // Set the mode
    void setWindowLevel(int level);  // Set the window level
};

#endif
