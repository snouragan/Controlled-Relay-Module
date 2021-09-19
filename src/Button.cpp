#include "Button.h"

Button::Button(int buttonPin, int controlledRelay) {
      this->buttonPin = buttonPin;
      this->controlledRelay = controlledRelay;
    }

bool Button::pressed() {
      lastButtonState = currentButtonState;
      currentButtonState = digitalRead(buttonPin);
      if(lastButtonState == HIGH && currentButtonState == LOW)
        return 1;
      return 0;
    }
int Button::getControlledRelay(){
      return controlledRelay;
    }