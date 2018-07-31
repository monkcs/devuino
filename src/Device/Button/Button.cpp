#include "Button.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        Button<T>::Button(T pin, pin::Resistor pull, bool debounce)
            : pin(pin), InputDigital(debounce)
        {
            this->pin.initiate(pin::Mode::InputDigital, pull);
        }

        template <typename T>
        bool Button<T>::value()
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