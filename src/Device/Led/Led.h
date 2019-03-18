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

            void brightness(const int value) override
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
