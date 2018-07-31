#ifndef BUTTON_H
#define BUTTON_H

#include "InputDigital.h"

namespace devuino
{
    namespace device
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
        };
    }
}

#endif