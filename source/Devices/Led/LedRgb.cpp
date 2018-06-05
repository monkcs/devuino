#include <Arduino.h>
#include "LedRgb.h"

namespace devuino
{
    LedRgb::LedRgb(byte redpin, byte greenpin, byte bluepin)
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

    void LedRgb::off()
    {
        brightness(0);
    }

    void LedRgb::on()
    {
        brightness(255);
    }

    void LedRgb::red(byte value)
    {
        change(pins[0], value);
    }

    void LedRgb::green(byte value)
    {
        change(pins[1], value);
    }

    void LedRgb::blue(byte value)
    {
        change(pins[2], value);
    }

    void LedRgb::change(byte pin, byte value)
    {
        analogWrite(pin, (byte)(value * (bright / 255)));
    }
}