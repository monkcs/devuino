#ifndef RGB_H
#define RGB_H

#include "../Light.h"

namespace devuino
{
    class Rgb : public Light
    {
      public:
        void brightness(int value);
        void colour(long hexadecimal);
        void colour(byte r, byte g, byte b);
        virtual void red(byte value) = 0;
        virtual void green(byte value) = 0;
        virtual void blue(byte value) = 0;

      protected:
        byte r, g, b = 0;
    };
}
#endif
