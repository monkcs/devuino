#ifndef BUTTON_H
#define BUTTON_H

#include "InputDigital.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        /* Debounce not yet implemented */
        template <typename T>
        class Button : public InputDigital
        {
          public:
            Button(T pin, pin::Resistor pull, bool debounce = true);

            bool value() override;

          protected:
            T pin;
        };
    }
}

#endif