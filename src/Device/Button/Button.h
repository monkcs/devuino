#ifndef BUTTON_H
#define BUTTON_H

#include "InputDigital.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        /* Debounce not yet implemented */
        template <typename T>
        class Button : public InputDigital
        {
          public:
            Button(T pin, pin::Resistor pull, bool debounce = true)
                : pin(pin), InputDigital(debounce)
            {
                this->pin.initiate(pin::Mode::InputDigital, pull);
            }

            bool value() override
            {
                /*if (debounce)
                {
                }
                else*/
                {
                    return pin.digitalread();
                }
            }

          protected:
            T pin;
        };
    }
}

#include "Button.cpp"

#endif
