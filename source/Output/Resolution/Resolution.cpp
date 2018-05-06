#include "Resolution.h"

namespace devuino
{
    int Resolution::resolution()
    {
        return bitresolution;
    }
    void Resolution::resolution(int bits)
    {
        bitresolution = bits;
    }
}