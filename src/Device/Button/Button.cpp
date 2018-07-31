#include "Button.h"

namespace devuino
{
    namespace device
    {
        Button::Button(T pin, bool debounce, pin::Resistor pull)
            : pin(pin), InputDigital(debounce)
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
}