#include <Arduino.h>
#include "Button.h"

// SHIFT_REGISTER:
const int dataPin = 10;
const int latchPin = 11;
const int clockPin = 12; 
byte state = 0b11111111;

// RELAY:
bool relayState[3] = {0, 0, 0};

// BUTTON:
const int numberOfButtons = 3;
int buttonPins[numberOfButtons] = {2, 3, 6}; 
Button button[] = {Button(2, 2), Button(3, 3), Button(6, 4)};

void openLatch() {
  digitalWrite(latchPin, 0);
  digitalWrite(latchPin, 1);
}

void sendByte(byte data) {
  shiftOut(dataPin, clockPin, MSBFIRST, data);
  openLatch();
}

// void sendByteOnButtonPress(Button button) {
//   if(button.pressed()) {
//     Serial.print(F("State: "));
//     Serial.println(state, BIN);
//     if(relayState) {
//       state += 0b00000001 << 0;
//     }
//     else state -= 0b00000001 << 0;
//     relayState = !relayState;
//     Serial.print(F("Updated state: "));
//     Serial.println(state, BIN);
//   }
//   sendByte(state);
// }

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

// TESTS:
void test1 () {
  sendByte(state);
  delay(1000);
  sendByte(~state);
  delay(1000);
}
void test2 () {
  if(button[buttonCounter].pressed()) {
    Serial.print(F("State: "));
    Serial.println(state, BIN);
    if(relayState[buttonCounter]) {
      state += 0b00000001 << button[buttonCounter].getControlledRelay();
      Serial.print(F("Add: "));
    Serial.println(0b00000001 << button[buttonCounter].getControlledRelay(), BIN);
    }
    else {
      Serial.print(F("Sub: "));
      Serial.println(0b00000001 << button[buttonCounter].getControlledRelay(), BIN);
      state -= 0b00000001 << button[buttonCounter].getControlledRelay();
    }
    relayState[buttonCounter] = !relayState[buttonCounter];
    Serial.print(F("Updated state: "));
    Serial.println(state, BIN);
  }
  sendByte(state);
  buttonCounter++;
  if(buttonCounter == numberOfButtons)
    buttonCounter=0;
}

void loop() {
    if(button[buttonCounter].pressed()) {
    Serial.print(F("State: "));
    Serial.println(state, BIN);
    if(relayState[buttonCounter]) {
      state += 0b00000001 << button[buttonCounter].getControlledRelay();
      Serial.print(F("Add: "));
    Serial.println(0b00000001 << button[buttonCounter].getControlledRelay(), BIN);
    }
    else {
      Serial.print(F("Sub: "));
      Serial.println(0b00000001 << button[buttonCounter].getControlledRelay(), BIN);
      state -= 0b00000001 << button[buttonCounter].getControlledRelay();
    }
    relayState[buttonCounter] = !relayState[buttonCounter];
    Serial.print(F("Updated state: "));
    Serial.println(state, BIN);
  }
  sendByte(state);
  buttonCounter++;
  if(buttonCounter == numberOfButtons)
    buttonCounter=0;
}