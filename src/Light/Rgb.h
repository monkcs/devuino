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
        void colour(const unsigned long hexadecimal) const;
        void colour(const byte r, const byte g, const byte b);
        virtual void red(const byte value) = 0;
        virtual void green(const byte value) = 0;
        virtual void blue(const byte value) = 0;

      protected:
        byte r, g, b = 0;
    };
}
#endif
