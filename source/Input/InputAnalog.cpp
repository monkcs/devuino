#include "InputAnalog.h"

namespace devuino
{
    InputAnalog::InputAnalog(int bitresolution, bool debounce)
        : bitsize(bitresolution), debounce(debounce)
    {
    }

    float InputAnalog::percent()
    {
        return (float)value() / (float)bitsize.resolution;
    }
}