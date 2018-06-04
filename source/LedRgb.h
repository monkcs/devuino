#ifndef LEDRGB_H
#define LEDRGB_H

#include <Arduino.h>
#include "OutputDigital.h"
#include "Rgb.h"

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
        byte pins[3];

      private:
        void change(byte pin, byte value);
    };
}

#endif