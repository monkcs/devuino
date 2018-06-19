#include <Arduino.h>
#include "Potentiometer.h"

namespace devuino
{
    Potentiometer::Potentiometer(byte pin, bool debounce, int bitresolution)
        : pin(pin), InputAnalog(bitresolution, debounce)
    {
        pinMode(pin, INPUT);
    }
    Potentiometer::~Potentiometer()
    {
    }

    int Potentiometer::value()
    {
     /* if (debounce)
        {
            
        }
        else */
        {
            return analogRead(pin);
        }
    }
}