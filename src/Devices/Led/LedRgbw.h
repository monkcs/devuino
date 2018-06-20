#ifndef LEDRGBW_H
#define LEDRGBW_H

#include "OutputDigital.h"
#include "Rgbw.h"
#include <Arduino.h>

namespace devuino
{
    class LedRgbw : public OutputDigital, public Rgbw
    {
      public:
        LedRgbw(byte redpin, byte greenpin, byte bluepin, byte whitepin);
        ~LedRgbw();

        void off() override;
        void on() override;
        void red(byte value) override;
        void green(byte value) override;
        void blue(byte value) override;
        void white(byte value) override;

      protected:
        void change(byte pin, byte value);
        byte pins[4];
    };
}

#endif