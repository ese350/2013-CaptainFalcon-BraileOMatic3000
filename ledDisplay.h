#ifndef MBED_LEDDISPLAY_H
#define MBED_LEDDISPLAY_H

#include "mbed.h"

class ledDisplay {
public:
    ledDisplay(PinName pin);
    void draw_pattern(int pattern);
    void drawChar(char character);
    
private:  
    DigitalOut _pin;
};
 
#endif