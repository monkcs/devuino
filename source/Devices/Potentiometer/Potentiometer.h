#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>
#include "InputAnalog.h"

namespace devuino
{
    /* Debounce not yet implemented */
    class Potentiometer : public InputAnalog
    {
      public:
        Potentiometer(byte pin, bool debounce = true, int bitresolution = 8);

        int value() override;

      protected:
        const byte pin;
    };
}

#endif