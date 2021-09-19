#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include <Arduino.h>

extern const int dataPin = 10;
extern const int latchPin = 11;
extern const int clockPin = 12; 

namespace sh {
    void openLatch() {
        digitalWrite(latchPin, 0);
        digitalWrite(latchPin, 1);
    }
    void sendByte(byte data) {
        shiftOut(dataPin, clockPin, MSBFIRST, data);
        openLatch();
    }
} 

#endif