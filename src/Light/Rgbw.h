#ifndef RGBW_H
#define RGBW_H

#include "Rgb.h"
#include <Arduino.h>

namespace devuino
{
    class Rgbw : public Rgb
    {
      public:
        void brightness(const unsigned int value) override
        {
            bright = value;
            colour(r, g, b, w);
        };

        void colour(const uint32_t hexadecimal) const
        {
            colour(static_cast<uint8_t>(hexadecimal >> 24),
                   static_cast<uint8_t>(hexadecimal >> 16),
                   static_cast<uint8_t>(hexadecimal >> 8),
                   static_cast<uint8_t>(hexadecimal));
        };

        void colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t w)
        {
            Rgb::colour(r, g, b);
            this->w = w;
            white(w);
        };

        virtual void white(const uint8_t value) = 0;

      protected:
        uint8_t w = 0;
    };
}

#endif
