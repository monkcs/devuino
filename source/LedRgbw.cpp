#include "LedRgbw.h"
#include <Arduino.h>

namespace devuino
{
    LedRgbw::LedRgbw(int redpin, int greenpin, int bluepin, int whitepin)
    {
        pins[0] = redpin;
        pins[1] = greenpin;
        pins[2] = bluepin;
        pins[3] = whitepin;

        for (auto pin : pins)
        {
            pinMode(pin, OUTPUT);
        }
    }

    LedRgbw::~LedRgbw()
    {
        off();
    }

    void LedRgbw::off()
    {
        brightness(0);
    }

    void LedRgbw::on()
    {
        brightness(255);
    }

    void LedRgbw::red(byte value)
    {
        change(pins[0], value);
    }

    void LedRgbw::green(byte value)
    {
        change(pins[1], value);
    }

    void LedRgbw::blue(byte value)
    {
        change(pins[2], value);
    }

    void LedRgbw::white(byte value)
    {
        change(pins[3], value);
    }

    void LedRgbw::change(int pin, byte value)
    {
        analogWrite(pin, (int)(value * (bright / 255)));
    }
}