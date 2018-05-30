#ifndef RGBW_H
#define RGBW_H

#include <Arduino.h>
#include "Rgb.h"

namespace devuino
{
    class Rgbw : public Rgb
    {
      public:
        void brightness(int value) override;
        void colour(long hexadecimal) override;
        void colour(byte red, byte green, byte blue, byte white);
        virtual void white(byte value) = 0;

      protected:
        byte w = 0;
    };
}

#endif