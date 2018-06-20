#include "Resolution.h"

namespace devuino
{
    Resolution::Resolution(int bits)
        : bits(bits), resolution(1 << bits)
    {
    }
}