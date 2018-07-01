#ifndef BUTTON_H
#define BUTTON_H

#include "InputDigital.h"
#include <Arduino.h>

namespace devuino
{
    /* Debounce not yet implemented */
    template <typename T>
    class Button : public InputDigital
    {
      public:
        Button(T pin, bool debounce = true, pin::Resistor pull);

        bool value() override;

      protected:
        T pin;
        const pin::Resistor pull;
    };
}

#endif