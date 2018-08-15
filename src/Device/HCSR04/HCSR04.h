#ifndef HCSR04_H
#define HCSR04_H

#include "Distance.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class HCSR04 : public Distance
        {
          public:
            HCSR04(T trigger, T echo, float minimum = 0.02, float maximum = 4.0)
                : trigger(trigger), echo(echo), minimum(minimum), maximum(maximum)
            {
                this->trigger.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
                this->echo.initiate(pin::Mode::InputDigital, pin::Resistor::None);
            }

            float metre() override
            {
                trigger.digitalwrite(false);
                delayMicroseconds(5);
                trigger.digitalwrite(true);
                delayMicroseconds(10);
                trigger.digitalwrite(false);

                float reading = pulseIn(echo.pin, true, 70) / 5800.0;

                if (reading > maximum)
                {
                    return maximum;
                }
                else if (reading < minimum)
                {
                    return minimum;
                }
                else
                {
                    return reading;
                }
            }

          private:
            const float minimum;
            const float maximum;
            T trigger;
            T echo;
        };
    }
}

#endif