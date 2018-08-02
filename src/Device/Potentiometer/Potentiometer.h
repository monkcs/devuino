#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "InputAnalog.h"

namespace devuino
{
    namespace device
    {
        /* Debounce not yet implemented */
        template <typename T>
        class Potentiometer : public InputAnalog
        {
          public:
            Potentiometer(T pin, bool debounce = true, int bitresolution = 8)
                : pin(pin), InputAnalog(bitresolution, debounce)
            {
                this->pin.initiate(pin::Mode::InputAnalog);
            }

            int value() override
            {
             /* if (debounce)
                {
                }
                else */
                {
                    return pin.analogread();
                }
            }

          protected:
            T pin;
        };
    }
}

#endif