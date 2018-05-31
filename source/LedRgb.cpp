#include "LedRgb.h"
#include <Arduino.h>

namespace devuino
{
    LedRgb::LedRgb(int redpin, int greenpin, int bluepin)
    {
        pins[0] = redpin;
        pins[1] = greenpin;
        pins[2] = bluepin;

        for (auto pin : pins)
        {
            pinMode(pin, OUTPUT);
        }
    }

    LedRgb::~LedRgb()
    {
        off();
    }

    void Led::off()
    {
        brightness(0);
    }

    void Led::on()
    {
        colour(r, g, b);
    }

    void red(byte value)
    {
        analogWrite(pins[0], value);
    }

    void green(byte value)
    {
        analogWrite(pins[1], value);
    }

    void blue(byte value)
    {
        analogWrite(pins[2], value);
    }
}