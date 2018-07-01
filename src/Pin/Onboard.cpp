#include "Onboard.h"

namespace devuino::pin
{
    Onboard::Onboard(int pin)
        : pin(pin)
    {
    }

    int Onboard::analogread()
    {
    }

    void Onboard::analogwrite(int value)
    {
    }

    bool Onboard::digitalread()
    {
    }

    void Onboard::digitalwrite(bool value)
    {
    }

    void Onboard::initiate(devuino::pin::Mode mode, Resistor pull = Resistor::None)
    {

        switch (mode)
        {
            case Mode::InputAnalog:
            {
            }
            break;

            case Mode::InputDigital:
            {
            }
            break;

            case Mode::OutputAnalog:
            {
            }
            break;

            case Mode::OutputDigital:
            {
            }
            break;
        }
    }
}