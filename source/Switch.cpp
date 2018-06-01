#include "Switch.h"
#include <Arduino.h>

namespace devuino
{
    Switch::Switch(int pin)
    {
        this->pin = pin;
        pinMode(pin, OUTPUT);
        off();
    }

    Switch::~Switch()
    {
        off();
    }

    void Switch::off()
    {
        change(false);
    }

    void Switch::on()
    {
        change(true);
    }

    void Switch::change(bool state)
    {
        active = state;
        digitalWrite(pin, state);
    }
}