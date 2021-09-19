#include <Arduino.h>
#include "Button.h"
#include "ShiftRegister.h"

// SHIFT_REGISTER:

byte state = 0b11111111;

// BUTTON:
const int numberOfButtons = 3;
int buttonPins[numberOfButtons] = {2, 3, 6}; 
Button button[] = {Button(2, 2), Button(3, 3), Button(6, 4)};

// RELAY:
bool relayState[3] = {0, 0, 0};

byte updateState(int buttonCounter) {
  if(button[buttonCounter].pressed()) {
      if(relayState[buttonCounter]) {
        state += 0b00000001 << button[buttonCounter].getControlledRelay();
        }
      else {
        state -= 0b00000001 << button[buttonCounter].getControlledRelay();
      }
      relayState[buttonCounter] = !relayState[buttonCounter];
  }
  return state;
}

void setup() {
  // SERIAL:
  Serial.begin(9600);
  // BUTTONS:
  for(int i=0; i<numberOfButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  // LED:
  pinMode(LED_BUILTIN, OUTPUT);
  // SHIFT_REGISTER:
  pinMode(dataPin, 1);
  pinMode(latchPin, 1);
  pinMode(clockPin, 1);
}

int buttonCounter = 0;

void loop() {
  state = updateState(buttonCounter);
  sh::sendByte(state);
  buttonCounter++;
  if(buttonCounter == numberOfButtons)
    buttonCounter=0;
}