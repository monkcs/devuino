#ifndef LEDRGBW_H
#define LEDRGBW_H

#include <Arduino.h>
#include "OutputDigital.h"
#include "Rgbw.h"

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
        byte pins[4];

      private:
        void change(byte pin, byte value);
    };
}

#endif