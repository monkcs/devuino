#ifndef TEMPERATURE_H
#define TEMPERATURE_H

namespace devuino
{
    class Temperature
    {
      public:
        virtual double celsius() const = 0;
        double fahrenheit() const;
        double kelvin() const;
    };
}

#endif
