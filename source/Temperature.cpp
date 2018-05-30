#include "Temperature.h"

namespace devuino
{
    float Temperature::fahrenheit()
    {
        return celsius() * (9.0 / 5.0) + 32.0;
    }

    float Temperature::kelvin()
    {
        return celsius() + 273.15;
    }
}