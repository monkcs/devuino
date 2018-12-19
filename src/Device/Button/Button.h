#ifndef BUTTON_H
#define BUTTON_H

#include "../../Input/InputDigital.h"
#include "../../Pin/Pin.h"

namespace devuino
{
    namespace device
    {
        /* Debounce not yet implemented */
        template <typename T>
        class Button : public InputDigital
        {
          public:
            Button(T pin, devuino::pin::Resistor pull, bool debounce = true)
                : pin(pin), InputDigital(debounce)
            {
                this->pin.initiate(devuino::pin::Mode::InputDigital, pull);
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

#endif
