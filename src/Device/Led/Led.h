#ifndef LED_H
#define LED_H

#include "../../Light/Light.h"
#include "../../Output/OutputDigital.h"
#include "../../Pin/Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Led : public Light, public OutputDigital
        {
          public:
            Led(const T pin, const int bitresolution = 10)
                : pin(pin), Light(bitresolution)
            {
                this->pin.initiate(pin::Mode::OutputAnalog);
            }

            ~Led()
            {
                off();
            }

            void operator= (const bool value) const
            {
                set(value);
            }

            unsigned int brightness() const override
            {
                return pin.analogread();
            }

            void brightness(const unsigned int value) override
            {
                pin.analogwrite(value);
            }

            void off() override
            {
                brightness(bitsize.minimum());
            }

            void on() override
            {
                brightness(bitsize.maximum());
            }

          protected:
            const T pin;
        };
    }
}
#endif
