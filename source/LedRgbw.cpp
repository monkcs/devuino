#include <Arduino.h>
#include "LedRgbw.h"

namespace devuino
{
    LedRgbw::LedRgbw(byte redpin, byte greenpin, byte bluepin, byte whitepin)
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

    void LedRgbw::change(byte pin, byte value)
    {
        analogWrite(pin, (byte)(value * (bright / 255)));
    }
}