#ifndef HCSR04_H
#define HCSR04_H

#include "../../Distance/Distance.h"
#include "../../Delay/DelaySync.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class HCSR04 : public DistanceOutput
        {
          public:
            HCSR04(const T trigger, const T echo, const Lenght minimum = 2_cm, const Lenght maximum = 4_metre)
                : trigger(trigger), echo(echo), minimum(minimum), maximum(maximum)
            {
                this->trigger.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
                this->echo.initiate(pin::Mode::InputDigital, pin::Resistor::None);
            }

            Lenght distance() override
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

                const Lenght reading = Lenght(pulseIn(13/*echo.pin*/, true, 70) / 5800.0);

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
            const Lenght minimum;
            const Lenght maximum;
            const T trigger;
            const T echo;
        };
    }
}

#endif
