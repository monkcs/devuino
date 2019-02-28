#include "InputAnalog.h"

namespace devuino
{
    InputAnalog::InputAnalog(int bitresolution, bool debounce)
        : bitsize(bitresolution), debounce(debounce)
    {
    }

    double InputAnalog::percent()
    {
        return (double)value() / (double)(bitsize.resolution - 1);
    }
}
