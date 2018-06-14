#ifndef LEDRGB_H
#define LEDRGB_H

#include "OutputDigital.h"
#include "Rgb.h"
#include <Arduino.h>

namespace devuino
{
    class LedRgb : public OutputDigital, public Rgb
    {
      public:
        LedRgb(byte redpin, byte greenpin, byte bluepin);
        ~LedRgb();

        void off() override;
        void on() override;
        void red(byte value) override;
        void green(byte value) override;
        void blue(byte value) override;

      protected:
        void change(byte pin, byte value);
        byte pins[3];
    };
}

#endif