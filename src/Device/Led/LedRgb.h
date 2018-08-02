#ifndef LEDRGB_H
#define LEDRGB_H

#include "OutputDigital.h"
#include "Rgb.h"
#include <Arduino.h>

namespace devuino
{
    namespace device
    {
        template <typename T>
        class LedRgb : public OutputDigital, public Rgb
        {
          public:
            LedRgb(T redpin, T greenpin, T bluepin)
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

            void red(byte value) override
            {
                change(pins[0], value);
            }

            void green(byte value) override
            {
                change(pins[1], value);
            }
            
            void blue(byte value) override
            {
                change(pins[2], value);
            }

          protected:
            T pins[3];

            void change(T pin, byte value)
            {
                pin.analogwrite((byte)(value * (bright / 255)));
            }
        };
    }
}
#endif