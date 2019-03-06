#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "../../Input/InputAnalog.h"
#include "../../Delay/DelaySync.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Resistance : public InputAnalog
        {
          public:

            /* Make a reading of a analog input from (T signal) by powering on a resistor from the (T power) pin.
             * That to prevent for example powerdraw and corrosion on water sensors. */

            Resistance(T signal, T power, bool debounce = false, uint8_t iterations = 10, uint8_t bitresolution = 8)
                : signal(signal), power(power), iterations(iterations), InputAnalog(bitresolution, debounce)
            {
                this->signal.initiate(pin::Mode::InputAnalog);
                this->power.initiate(pin::Mode::OutputDigital);
            }

            int value() override
            {
                power.digitalwrite(true);
                int value = 0;

                if (debounce)
                {
                    int reading = 0;
                    for (uint8_t counter = 0; counter < iterations; counter++)
                    {
                        reading += signal.analogread();
                        DelaySync(5);
                    }
                    value = reading / iterations;
                }
                else
                {
                    value = signal.analogread();
                }

                power.digitalwrite(false);
                return value;
            }

          protected:
            T signal;
            T power;
            const uint8_t iterations;
        };
    }
}

#endif
