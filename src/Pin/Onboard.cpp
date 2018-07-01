#include "Onboard.h"
#include <Arduino.h>

namespace devuino::pin
{
    Onboard::Onboard(byte pin)
        : pin(pin)
    {
    }

    int Onboard::analogread()
    {
        return analogRead(pin);
    }

    void Onboard::analogwrite(int value)
    {
        analogWrite(pin, value);
    }

    bool Onboard::digitalread()
    {
        digitalRead(pin);
    }

    void Onboard::digitalwrite(bool value)
    {
        digitalWrite(pin, value);
    }

    void Onboard::initiate(devuino::pin::Mode mode, Resistor pull = Resistor::None)
    {

        switch (mode)
        {
            case Mode::InputAnalog:
            case Mode::InputDigital:
            {
                if (pull == Resistor::PullUp)
                {
                    pinMode(pin, INPUT_PULLUP);
                }
                else
                {
                    pinMode(pin, INPUT);
                }
            }
            break;

            case Mode::OutputAnalog:
            case Mode::OutputDigital:
            {
                pinMode(pin, OUTPUT);
            }
            break;
        }
    }
}