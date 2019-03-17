#include "Temperature.h"

namespace devuino
{
    double Temperature::fahrenheit() const
    {
        return celsius() * (9.0 / 5.0) + 32.0;
    }

    double Temperature::kelvin() const
    {
        return celsius() + 273.15;
    }
}
