#ifndef HCSR04_H
#define HCSR04_H

#include "../../Distance/Distance.h"
#include "../../Delay/DelaySync.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class HCSR04 : public Distance
        {
          public:
            HCSR04(T trigger, T echo, double minimum = 0.02, double maximum = 4.0)
                : trigger(trigger), echo(echo), minimum(minimum), maximum(maximum)
            {
                this->trigger.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
                this->echo.initiate(pin::Mode::InputDigital, pin::Resistor::None);
            }

            double metre() override
            {
                /*
                   To trigger a distance reading, a 10 microsecond
                   high on the trigger pin needs to happend.

                   To get the distance in metre, divide the reading
                   by 5800.
                */
                trigger.digitalwrite(false);
                DelaySync(5);
                trigger.digitalwrite(true);
                DelaySync(10);
                trigger.digitalwrite(false);

                double reading = pulseIn(echo.pin, true, 70) / 5800.0;

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
            const double minimum;
            const double maximum;
            T trigger;
            T echo;
        };
    }
}

#endif
