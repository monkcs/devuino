#include "Button.h"
#include <Arduino.h>

namespace devuino::device
{
    Button::Button(T pin, bool debounce, pin::Resistor pull)
        : pin(pin), InputDigital(debounce), pull(pull)
    {
        this->pin.initiate(pin::Mode::InputDigital, pull);
    }

    bool Button::value()
    {
        /* if (debounce)
        {
            
        }
        else */
        {
            return pin.digitalread();
        }
    }
}