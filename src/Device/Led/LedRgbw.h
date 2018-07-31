#ifndef LEDRGBW_H
#define LEDRGBW_H

#include "OutputDigital.h"
#include "Rgbw.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class LedRgbw : public OutputDigital, public Rgbw
        {
          public:
            LedRgbw(T redpin, T greenpin, T bluepin, T whitepin);
            ~LedRgbw();

            void off() override;
            void on() override;
            void red(byte value) override;
            void green(byte value) override;
            void blue(byte value) override;
            void white(byte value) override;

          protected:
            void change(T pin, byte value);
            T pins[4];
        };
    }
}

#endif