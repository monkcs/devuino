#include "Light.h"

namespace devuino
{
    Light::Light(int bitresolution)
        : bitsize(bitresolution)
    {
    }
    int Light::brightness()
    {
        return bright;
    }
    void Light::brightness(float percent)
    {
        brightness((int)((bitsize.resolution - 1) * percent));
    }
}