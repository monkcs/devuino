#include "Led.h"
#include <Arduino.h>

namespace devuino::device
{
    Led::Led(T pin, int bitresolution)
        : pin(pin), Light(bitresolution)
    {
        this->pin.initiate(pin::Mode::OutputAnalog);
    }

    Led::~Led()
    {
        off();
    }

    void Led::brightness(int value)
    {
        bright = value;
        pin.analogwrite(value);
    }

    void Led::off()
    {
        brightness(0);
    }

    void Led::on()
    {
        brightness(bitsize.resolution - 1);
    }
}