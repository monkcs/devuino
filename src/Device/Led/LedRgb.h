#ifndef LEDRGB_H
#define LEDRGB_H

#include "OutputDigital.h"
#include "Rgb.h"
namespace devuino::device
{
    template <typename T>
    class LedRgb : public OutputDigital, public Rgb
    {
      public:
        LedRgb(T redpin, T greenpin, T bluepin);
        ~LedRgb();

        void off() override;
        void on() override;
        void red(byte value) override;
        void green(byte value) override;
        void blue(byte value) override;

      protected:
        void change(T pin, byte value);
        T pins[3];
    };
}

#endif