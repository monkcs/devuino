#include "Button.h"
#include <Arduino.h>

namespace devuino
{
    Button::Button(byte pin, bool debounce)
        : pin(pin), InputDigital(debounce)
    {
        pinMode(pin, INPUT);
    }

    bool Button::value()
    {
        /* if (debounce)
        {
            
        }
        else */
        {
            return digitalRead(pin);
        }
    }
}