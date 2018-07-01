#include "LedRgb.h"

namespace devuino::device
{
    LedRgb::LedRgb(T redpin, T greenpin, T bluepin)
    {
        pins[0] = redpin;
        pins[1] = greenpin;
        pins[2] = bluepin;

        for (auto pin : pins)
        {
            pin.initiate(devuino::pin::Mode::OutputAnalog);
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

    void LedRgb::change(T pin, byte value)
    {
        pin.analogwrite((byte)(value * (bright / 255)));
    }
}