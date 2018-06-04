#include "Led.h"
#include <Arduino.h>

namespace devuino
{
    Led::Led(byte pin, int bitresolution)
        : Light(bitresolution), pin(pin)
    {
        pinMode(pin, OUTPUT);
    }

    Led::~Led()
    {
        off();
    }

    void Led::brightness(int value)
    {
        bright = value;
        analogWrite(pin, value);
    }

    void Led::off()
    {
        brightness(0);
    }

    void Led::on()
    {
        brightness(bitsize.resolution());
    }
}