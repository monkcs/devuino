#ifndef RGB_H
#define RGB_H

#include <stdint.h>

#include "Colour.h"
#include "Light.h"

namespace devuino
{
    class Rgb : public Light
    {
      public:
        constexpr Rgb(const Colour colours)
            : Light(Resolution(8)), colours(colours){};

        unsigned int brightness() const
        {
            return bright;
        };

        void brightness(const unsigned int value) override
        {
            bright = value;
            update();
        };

        void colour(const Colour colours)
        {
            this->colours = colours;
            update();
        };

        void red(const uint8_t value)
        {
            colours.red = value;
            update();
        };

        void green(const uint8_t value)
        {
            colours.green = value;
            update();
        };

        void blue(const uint8_t value)
        {
            colours.blue = value;
            update();
        };

        virtual void update() const = 0;

        Colour colours;
    };
}
#endif
