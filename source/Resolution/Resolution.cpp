#include "Resolution.h"

namespace devuino
{
    int Resolution::resolution()
    {
        return bitresolution * 8;
    }
    void Resolution::resolution(byte bits)
    {
        bitresolution = bits;
    }
}