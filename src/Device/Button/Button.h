#ifndef BUTTON_H
#define BUTTON_H

#include "../../Input/InputDigital.h"
#include "../../Pin/Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Button final : public InputDigital
        {
          public:
            Button(const T pin, const devuino::pin::Resistor pull)
                : InputDigital(false), pin(pin), pull(pull)
            {
                this->pin.initiate(devuino::pin::Input::Digital, pull);
            };

            bool value() const override
            {
                const bool reading = pin.digitalread();
                return (pull == devuino::pin::Resistor::PullUp) ? !reading : reading;
            };

          protected:
            T pin;
            devuino::pin::Resistor pull;
        };
    }
}

#endif
