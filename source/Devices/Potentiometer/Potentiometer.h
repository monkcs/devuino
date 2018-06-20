#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

namespace devuino
{
    /* Debounce not yet implemented */
    class Potentiometer : public pin, public InputAnalog
    {
      public:
        Potentiometer(byte pin, bool debounce = true, int bitresolution = 8);

        int value() override;

      protected:
        const byte pin;
    };
}

#endif