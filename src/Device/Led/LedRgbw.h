#ifndef LEDRGBW_H
#define LEDRGBW_H

#include "../../Light/Rgbw.h"
#include "../../Output/OutputDigital.h"
#include <Arduino.h>

namespace devuino
{
    namespace device
    {
        template <typename T>
        class LedRgbw : public OutputDigital, public Rgbw
        {
          public:
            LedRgbw(T redpin, T greenpin, T bluepin, T whitepin)
            {
                pins[0] = redpin;
                pins[1] = greenpin;
                pins[2] = bluepin;
                pins[3] = whitepin;

                for (auto pin : pins)
                {
                    pin.initiate(pin::Mode::OutputAnalog);
                }
            }
            ~LedRgbw()
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
            
            void white(byte value) override
            {
                change(pins[3], value);
            }

          protected:
            T pins[4];

            void change(T pin, byte value)
            {
                pin.analogwrite((byte)(value * (bright / 255)));
            }
        };
    }
}

#endif