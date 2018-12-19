#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../../Input/InputAnalog.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Potentiometer : public InputAnalog
        {
          public:
            Potentiometer(T pin, bool debounce = false, int bitresolution = 8)
                : pin(pin), InputAnalog(bitresolution, debounce)
            {
                this->pin.initiate(pin::Mode::InputAnalog);
            }

            int value() override
            {
                if (debounce)
                {
                    int reading = 0;
                    const int iterations = 10;
                    for (int counter = 0; counter < iterations; counter++)
                    {
                        reading += pin.analogread();
                        delay(5);
                    }
                    return reading / iterations;
                }
                else
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