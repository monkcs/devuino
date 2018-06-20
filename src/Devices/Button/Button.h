#ifndef BUTTON_H
#define BUTTON_H

#include "InputDigital.h"
#include <Arduino.h>

namespace devuino
{
    /* Debounce not yet implemented */
    class Button : public InputDigital
    {
      public:
        Button(byte pin, bool debounce = true);

        bool value() override;

      protected:
        const byte pin;
    };
}

#endif