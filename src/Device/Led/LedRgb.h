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
            LedRgb(const T redpin, const T greenpin, const T bluepin, const Colour colours = { 0, 0, 0 })
              : Rgb { colours }, pins { redpin, greenpin, bluepin }
            {
                for (auto &pin : pins)
                {
                    pin.initiate(pin::Mode::OutputAnalog);
                }
                change();
            }
            ~LedRgb()
            {
                off();
            }

            void operator= (const bool value) const
            {
                set(value);
            }

            void operator= (const Colour colours)
            {
                this->colours = colours;
                change();
            }

            constexpr unsigned int brightness() const override
            {
                return bright;
            }

            void brightness(const unsigned int value) override
            {
                //Rgb::brightness(value);
                this->bright = value;
                change();
            }

          private:
            const T pins[3];

            void change() const override
            {
                for (auto index = 0; index < 3; index++)
                {
                    const auto value = static_cast<uint8_t>(colours[index] * (bright / 255.0));
                    pins[index].analogwrite(value);
                }
            }

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
