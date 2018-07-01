#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "InputAnalog.h"
#include <Arduino.h>

namespace devuino::device
{
    /* Debounce not yet implemented */
    template <typename T>
    class Potentiometer : public InputAnalog
    {
      public:
        Potentiometer(T pin, bool debounce = true, int bitresolution = 8);

        int value() override;

      protected:
        T pin;
    };
}

#endif