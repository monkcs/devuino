#ifndef RGB_H
#define RGB_H

#include "Light.h"
#include "Colour.h"

namespace devuino
{
    class Rgb : public Light
    {
      public:
        constexpr Rgb(const Colour colours) : Light(Resolution(8)), colours(colours)
        { };

        void brightness(const unsigned int value) override
        {
            this->bright = value;
            change();
        };

        void colour(const Colour colours)
        {
            this->colours = colours;
            change();
        };

        void red(const uint8_t value)
        {
            colours.red = value;
            change();
        };

        void green(const uint8_t value)
        {
            colours.green = value;
            change();
        };

        void blue(const uint8_t value)
        {
            colours.blue = value;
            change();
        };

      protected:
        Colour colours;

        virtual void change() const = 0;
    };
}
#endif
