#ifndef RGB_H
#define RGB_H

#include "Light.h"
#include <Arduino.h>

namespace devuino
{
    class Rgb : public Light
    {
      public:
        Rgb();
        void brightness(const int value) override;
        void colour(const uint32_t hexadecimal) const;
        void colour(const uint8_t r, const uint8_t g, const uint8_t b);
        virtual void red(const uint8_t value) = 0;
        virtual void green(const uint8_t value) = 0;
        virtual void blue(const uint8_t value) = 0;

      protected:
        uint8_t r, g, b = 0;
    };
}
#endif
