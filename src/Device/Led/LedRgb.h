#ifndef LEDRGB_H
#define LEDRGB_H

#include "../../Light/Rgb.h"
#include "../../Output/OutputDigital.h"
#include "../../Pin/Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class LedRgb : public OutputDigital, public Rgb
        {
          public:
            LedRgb(const T redpin, const T greenpin, const T bluepin) : Rgb(), pins {redpin, greenpin, bluepin}
            {
                for (auto &pin : pins)
                {
                    pin.initiate(pin::Mode::OutputAnalog);
                }
            }
            ~LedRgb()
            {
                off();
            }

            void operator= (const bool value) const
            {
                set(value);
            }

            void off() override
            {
                brightness(bitsize.range.minimum);
            }

            void on() override
            {
                brightness(bitsize.range.maximum);
            }

            void red(const uint8_t value) override
            {
                change(pins[0], value);
            }

            void green(const uint8_t value) override
            {
                change(pins[1], value);
            }
            
            void blue(const uint8_t value) override
            {
                change(pins[2], value);
            }

          protected:
            const T pins[3];

            void change(const T &pin, const uint8_t value)
            {
                pin.analogwrite(static_cast<uint8_t>((value * (bright / 255))));
            }
        };
    }
}

#endif
