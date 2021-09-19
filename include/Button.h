#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  private:
    bool lastButtonState;
    bool currentButtonState = 1;
    int buttonPin;
    int controlledRelay;
  public:
    Button(int buttonPin, int controlledRelay);
    bool pressed();
    int getControlledRelay();
};

#endif

