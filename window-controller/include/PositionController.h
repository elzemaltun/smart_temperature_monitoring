#ifndef __POSITIONCONTROLLER__
#define __POSITIONCONTROLLER__

#include <Arduino.h>

class PositionController {
public:
    PositionController(int pin);
    void init();
    int getPercentage();

private:
    int pin;
};

#endif
