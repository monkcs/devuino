#ifndef LEDRGBW_H
#define LEDRGBW_H

#include "../../Light/Rgbw.h"
#include "../../Output/OutputDigital.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class LedRgbw : public OutputDigital, public Rgbw
        {
          public:
            LedRgbw(const T redpin, const T greenpin, const T bluepin, const T whitepin) : Rgbw(), pins {redpin, greenpin, bluepin, whitepin}
            {
                for (auto &pin : pins)
                {
                    pin.initiate(pin::Mode::OutputAnalog);
                }
            }
            ~LedRgbw()
            {
                off();
            }

            void operator= (const bool value) const
            {
                set(value);
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
            
            void white(const uint8_t value) override
            {
                change(pins[3], value);
            }

          private:
            const T pins[4];

            void change(const T &pin, const uint8_t value)
            {
                pin.analogwrite(static_cast<uint8_t>((value * (bright / 255.0))));
            }

            void set(const bool value) override
            {
                brightness(value ? bright : bitsize.minimum());
            }
        };
    }
}

#endif
