#include "Resolution.h"

namespace devuino
{
    Resolution::Resolution(unsigned int bits)
        : bits(bits), resolution(1u << bits)
    {
    }
}