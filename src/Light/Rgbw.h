#ifndef RGBW_H
#define RGBW_H

#include "Rgb.h"
#include <Arduino.h>

namespace devuino
{
    class Rgbw : public Rgb
    {
      public:
        void brightness(const int value) override;
        void colour(const unsigned long hexadecimal) const;
        void colour(const byte red, const byte green, const byte blue, const byte white);
        virtual void white(const byte value) = 0;

      protected:
        byte w = 0;
    };
}

#endif
