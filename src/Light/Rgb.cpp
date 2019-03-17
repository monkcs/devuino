#include "Rgb.h"

namespace devuino
{
    Rgb::Rgb()
        : Light(8)
    {
    }
    void Rgb::brightness(const int value)
    {
        bright = value;
        colour(r, g, b);
    }

    void Rgb::colour(const uint32_t hexadecimal) const
    {
        colour((uint8_t)(hexadecimal >> 16), (uint8_t)(hexadecimal >> 8),
               (uint8_t)(hexadecimal));
    }

    void Rgb::colour(const uint8_t r, const uint8_t g, const uint8_t b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        red(r);
        green(g);
        blue(b);
    }
}
