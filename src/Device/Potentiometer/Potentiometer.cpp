#include "Potentiometer.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        Potentiometer<T>::Potentiometer(T pin, bool debounce, int bitresolution)
            : pin(pin), InputAnalog(bitresolution, debounce)
        {
            this->pin.initiate(pin::Mode::InputAnalog);
        }

        template <typename T>
        int Potentiometer<T>::value()
        {
            /* if (debounce)
        {
            
        }
        else */
            {
                return pin.analogread();
            }
        }
    }
}