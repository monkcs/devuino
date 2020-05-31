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
        class Led final : public Light, public OutputDigital
        {
          public:
            Led(const T pin, const Resolution bitresolution = Resolution(10)) : pin(pin), Light(bitresolution)
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
                return bright;
            }

            void brightness(const unsigned int value) override
            {
                bright = value;
                pin.analogwrite(bright);
            }

          protected:
            const T pin;

            void set(const bool value) override
            {
                brightness(value ? bright : bitsize.minimum());
            }

            bool status() const override
            {
                return (bright != 0);
            }
        };
    }
}
#endif
