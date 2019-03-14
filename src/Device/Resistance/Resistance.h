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

            Resistance(const T signal, const T power, const bool debounce = false, const uint8_t iterations = 10, const uint8_t bitresolution = 8)
                : signal(signal), power(power), iterations(iterations), InputAnalog(bitresolution, debounce)
            {
                this->signal.initiate(pin::Mode::InputAnalog);
                this->power.initiate(pin::Mode::OutputDigital);
            }

            int value() override
            {
                power.digitalwrite(true);

                if (debounce)
                {
                    int reading = 0;
                    for (auto counter = 0; counter < iterations; ++counter)
                    {
                        reading += signal.analogread();
                        DelaySync(5);
                    }
                    power.digitalwrite(false);
                    return reading / iterations;
                }
                else
                {
                    const int reading = signal.analogread();
                    power.digitalwrite(false);
                    return reading;
                }
            }

          protected:
            T signal;
            T power;
            const uint8_t iterations;
        };
    }
}

#endif
