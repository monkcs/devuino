#include "LedRgbw.h"

namespace devuino::device
{
    LedRgbw::LedRgbw(T redpin, T greenpin, T bluepin, T whitepin)
    {
        pins[0] = redpin;
        pins[1] = greenpin;
        pins[2] = bluepin;
        pins[3] = whitepin;

        for (auto pin : pins)
        {
            pin.initiate(devuino::pin::Mode::OutputAnalog);
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

    void LedRgbw::change(T pin, byte value)
    {
        pin.analogwrite((byte)(value * (bright / 255)));
    }
}