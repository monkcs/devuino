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
            Button(const T pin, const devuino::pin::Resistor pull, const bool debounce = true)
                : pin(pin), pull(pull), InputDigital(debounce)
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
                    return (pull == devuino::pin::Resistor::PullUp) ? !pin.digitalread() : pin.digitalread();
                }
            }

          protected:
            const T pin;
            const devuino::pin::Resistor pull;
        };
    }
}

#endif
