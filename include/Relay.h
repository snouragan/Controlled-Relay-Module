#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "Button.h"

class Relay {
    private:
        Button button;
    public:
        Relay(Button button);
};

#endif