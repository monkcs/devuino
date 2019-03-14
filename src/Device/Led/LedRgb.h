#ifndef LEDRGB_H
#define LEDRGB_H

#include "../../Light/Rgb.h"
#include "../../Output/OutputDigital.h"
#include <Arduino.h>

namespace devuino
{
    namespace device
    {
        template <typename T>
        class LedRgb : public OutputDigital, public Rgb
        {
          public:
            LedRgb(const T redpin, const T greenpin, const T bluepin)
            {
                pins[0] = redpin;
                pins[1] = greenpin;
                pins[2] = bluepin;

                for (auto pin : pins)
                {
                    pin.initiate(pin::Mode::OutputAnalog);
                }
            }
            ~LedRgb()
            {
                off();
            }

            void off() override
            {
                brightness(0);
            }

            void on() override
            {
                brightness(255);
            }

            void red(const byte value) override
            {
                change(pins[0], value);
            }

            void green(const byte value) override
            {
                change(pins[1], value);
            }
            
            void blue(const byte value) override
            {
                change(pins[2], value);
            }

          protected:
            T pins[3];

            void change(T pin, const byte value)
            {
                pin.analogwrite((byte)(value * (bright / 255)));
            }
        };
    }
}
#endif
