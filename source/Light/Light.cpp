#include "Light.h"

namespace devuino
{
    int Light::brightness()
    {
        return bright;
    }
    void Light::brightness(float percent)
    {
        brightness((int)(bitsize.resolution * percent));
    }
}