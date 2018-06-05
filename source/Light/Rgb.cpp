#include "Rgb.h"

namespace devuino
{
    Rgb::Rgb()
        : Light(8)
    {
    }
    void Rgb::brightness(int value)
    {
        bright = value;
        colour(r, g, b);
    }

    void Rgb::colour(long hexadecimal)
    {
        colour((byte)(hexadecimal >> 16), (byte)(hexadecimal >> 8),
               (byte)(hexadecimal));
    }

    void Rgb::colour(byte r, byte g, byte b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        red(r);
        green(g);
        blue(b);
    }
}