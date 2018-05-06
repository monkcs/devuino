#ifndef TEMPERATURE_H
#define TEMPERATURE_H

namespace devuino
{
    class Temperature
    {
      public:
        virtual float celsius() = 0;
        float fahrenheit();
        float kelvin();
    };
}

#endif
