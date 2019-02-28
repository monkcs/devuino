#include "Temperature.h"

namespace devuino
{
    double Temperature::fahrenheit()
    {
        return celsius() * (9.0 / 5.0) + 32.0;
    }

    double Temperature::kelvin()
    {
        return celsius() + 273.15;
    }
}
