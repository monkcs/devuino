#ifndef LEDRGB_H
#define LEDRGB_H

#include "Rgb.h"
#include "OutputDigital.h"

namespace devuino
{
    class LedRgb : public OutputDigital, public Rgb
    {
      public:
        LedRgb(int redpin, int greenpin, int bluepin);
        ~LedRgb();

        void off() override;
        void on() override;
        void red(byte value) override;
        void green(byte value) override;
        void blue(byte value) override;

      protected:
        int pins[3];
    };
}

#endif