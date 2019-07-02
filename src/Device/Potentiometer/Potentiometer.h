#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../../Input/InputAnalog.h"
#include "../../Delay/DelaySync.h"
#include "../../Pin/Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Potentiometer : public InputAnalog
        {
          public:
            Potentiometer(const T pin, const bool debounce = false, const unsigned int iterations = 10, const unsigned int bitresolution = 10)
                : pin(pin), iterations(iterations), InputAnalog(bitresolution, debounce)
            {
                this->pin.initiate(pin::Mode::InputAnalog);
            }

            int value() override
            {
                if (debounce)
                {
                    int reading = 0;
                    for (auto counter = 0; counter < iterations; counter++)
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
            const T pin;
            const unsigned int iterations;
        };
    }
}

#endif
