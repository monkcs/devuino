#ifndef LEDRGBW_H
#define LEDRGBW_H

#include "OutputDigital.h"
#include "Rgbw.h"

namespace devuino
{
    class LedRgbw : public OutputDigital, public Rgbw
    {
      public:
        LedRgbw(int redpin, int greenpin, int bluepin, int whitepin);
        ~LedRgbw();

        void off() override;
        void on() override;
        void red(byte value) override;
        void green(byte value) override;
        void blue(byte value) override;
        void white(byte value) override;

      protected:
        int pins[4];

      private:
        void change(int pin, byte value);
    };
}

#endif