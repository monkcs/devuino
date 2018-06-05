#include "Resolution.h"

namespace devuino
{
    Resolution::Resolution(int bits)
        : bitresolution(bits)
    {
    }
    int Resolution::bits()
    {
        return bitresolution;
    }
    int Resolution::resolution()
    {
        // Bitshift equals 2^n
        return 1 << bitresolution;
    }
}