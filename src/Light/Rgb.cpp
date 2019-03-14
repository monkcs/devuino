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

    void Rgb::colour(const unsigned long hexadecimal) const
    {
        colour((byte)(hexadecimal >> 16), (byte)(hexadecimal >> 8),
               (byte)(hexadecimal));
    }

    void Rgb::colour(const byte r, const byte g, const byte b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        red(r);
        green(g);
        blue(b);
    }
}
