#ifndef __WINDOWCONTROLTASK__
#define __WINDOWCONTROLTASK__

#include "Button.h"
#include "LcdController.h"
#include "ServoController.h"
#include "PositionController.h"

class WindowControlTask {
private:
    Button* button;
    LcdController* lcd;
    ServoController* servo;
    PositionController* potentiometer;
    int mode;  // 0 = AUTOMATIC, 1 = MANUAL
    uint8_t windowPercentage;
    float temperature;

    void handleAutomaticMode();
    void handleManualMode();

public:
    WindowControlTask(Button* button, LcdController* lcd, ServoController* servo, PositionController* potentiometer);
    void init();
    void tick();
};

#endif
