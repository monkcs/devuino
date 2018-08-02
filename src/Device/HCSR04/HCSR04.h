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
            HCSR04(T input, T output, float minimum = 0.02, float maximum = 4.0)
                : input(input), output(output), minimum(minimum), maximum(maximum)
            {
                this->input.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
                this->output.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
            }
            
            float distance() override
            {
                float reading = 0.0;

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
            T input;
            T output;
        };
    }
}

#endif