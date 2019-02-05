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
            Potentiometer(T pin, bool debounce = false, unsigned int iterations = 10, int bitresolution = 8)
                : pin(pin), iterations(iterations), InputAnalog(bitresolution, debounce)
            {
                this->pin.initiate(pin::Mode::InputAnalog);
            }

            int value() override
            {
                if (debounce)
                {
                    int reading = 0;
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
            const unsigned int iterations;
        };
    }
}

#endif
