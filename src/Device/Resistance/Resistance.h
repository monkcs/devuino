#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "../Switch/Switch.h"
#include "../Potentiometer/Potentiometer.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Resistance
        {
          public:

            /* Make a reading of a analog input from (T signal) by powering on a resistor from the (T power) pin.
             * That to prevent for example powerdraw and corrosion on water sensors. */

            Resistance(const T signal, const T power, const bool debounce = false, const unsigned int iterations = 10, const uint8_t bitresolution = 10)
                : signal(Potentiometer<T>(signal, debounce, iterations, bitresolution)), power(Switch<T>(power))
            {
            }

            int value() const
            {
                power.on();
                const auto reading = signal.value();
                power.off();

                return reading;
            }

            double percent() const
            {
                power.on();
                const auto reading = signal.percent();
                power.off();

                return reading;
            }

          protected:
            const Potentiometer<T> signal;
            const Switch<T> power;
        };
    }
}

#endif
