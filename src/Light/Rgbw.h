#ifndef RGBW_H
#define RGBW_H

#include "Rgb.h"
#include <Arduino.h>

namespace devuino
{
    class Rgbw : public Rgb
    {
      public:
        void brightness(int value) override;
        void colour(unsigned long hexadecimal);
        void colour(byte red, byte green, byte blue, byte white);
        virtual void white(byte value) = 0;

      protected:
        byte w = 0;
    };
}

#endif