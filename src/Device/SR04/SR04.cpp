#include "SR04.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        SR04<T>::SR04(T input, T output, float minimum, float maximum)
            : input(input), output(output), minimum(minimum), maximum(maximum)
        {
            this->input.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
            this->output.initiate(pin::Mode::OutputDigital, pin::Resistor::None);
        }

        template <typename T>
        float SR04<T>::metre()
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
    }
}