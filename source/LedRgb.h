#ifndef LEDRGB_H
#define LEDRGB_H

#include "OutputDigital.h"
#include "Rgb.h"

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

      private:
        void change(int pin, byte value);
    };
}

#endif