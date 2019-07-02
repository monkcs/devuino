#ifndef RGB_H
#define RGB_H

#include "Light.h"
#include <Arduino.h>

namespace devuino
{
    class Rgb : public Light
    {
      public:
        Rgb() : Light(8)
        { };

        void brightness(const int value) override
        {
            bright = value;
            colour(r, g, b);
        };

        void colour(const uint32_t hexadecimal) const
        {
            colour(static_cast<uint8_t>(hexadecimal >> 16),
                   static_cast<uint8_t>(hexadecimal >> 8),
                   static_cast<uint8_t>(hexadecimal));
        };

        void colour(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            red(r);
            green(g);
            blue(b);
        };

        virtual void red(const uint8_t value) = 0;
        virtual void green(const uint8_t value) = 0;
        virtual void blue(const uint8_t value) = 0;

      protected:
        uint8_t r, g, b = 0;
    };
}
#endif
