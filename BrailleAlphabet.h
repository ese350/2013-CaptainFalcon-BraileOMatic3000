#ifndef MBED_BRAILLEALPHABET_H
#define MBED_BRAILLEALPHABET_H
 
#include "mbed.h"

class BrailleAlphabet {
public:
    BrailleAlphabet(PinName pin);
    int matchCharacter(char character);
    bool isNumber(char c);
    
    
private:  
    DigitalOut _pin;
};
 
#endif