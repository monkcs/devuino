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
        void colour(const uint32_t hexadecimal) const;
        void colour(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t white);
        virtual void white(const uint8_t value) = 0;

      protected:
        uint8_t w = 0;
    };
}

#endif
