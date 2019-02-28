#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../../Input/InputAnalog.h"
#include "../../Delay/DelaySync.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Potentiometer : public InputAnalog
        {
          public:
            Potentiometer(T pin, bool debounce = false, uint8_t iterations = 10, uint8_t bitresolution = 8)
                : pin(pin), iterations(iterations), InputAnalog(bitresolution, debounce)
            {
                this->pin.initiate(pin::Mode::InputAnalog);
            }

            int value() override
            {
                if (debounce)
                {
                    int reading = 0;
                    for (uint8_t counter = 0; counter < iterations; counter++)
                    {
                        reading += pin.analogread();
                        DelaySync(5);
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
            const uint8_t iterations;
        };
    }
}

#endif
