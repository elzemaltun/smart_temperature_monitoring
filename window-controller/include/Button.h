#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

class Button {
public:
    Button(int pin);
    void init();
    bool isPressed();

private:
    int pin;
};

#endif
