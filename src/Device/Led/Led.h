#ifndef LED_H
#define LED_H

#include "Light.h"
#include "OutputDigital.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Led : public Light, public OutputDigital
        {
          public:
            Led(T pin, int bitresolution = 8)
                : pin(pin), Light(bitresolution)
            {
                this->pin.initiate(pin::Mode::OutputAnalog);
            }
            ~Led()
            {
                off();
            }

            void brightness(int value) override
            {
                bright = value;
                pin.analogwrite(value);
            }
            void off() override
            {
                brightness(0);
            }
            void on() override
            {
                brightness(bitsize.resolution - 1);
            }

          protected:
            T pin;
        };
    }
}
#endif