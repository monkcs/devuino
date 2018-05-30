#ifndef RGBW_H
#define RGBW_H

#include <Arduino.h>
#include "Rgb.h"

namespace devuino
{
    class Rgbw : public Rgb
    {
      public:
        void brightness(int value);
        void colour(long hexadecimal);
        void colour(byte red, byte green, byte blue, byte white);
        virtual void white(byte value) = 0;

      protected:
        byte w = 0;
    };
}

#endif