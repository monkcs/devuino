#include "Rgbw.h"

namespace devuino
{
    void Rgbw::brightness(const int value)
    {
        bright = value;
        colour(r, g, b, w);
    }

    void Rgbw::colour(const unsigned long hexadecimal) const
    {
        colour((byte)(hexadecimal >> 24), (byte)(hexadecimal >> 16), (byte)(hexadecimal >> 8), (byte)(hexadecimal));
    }

    void Rgbw::colour(const byte r, const byte g, const byte b, const byte w)
    {
        Rgb::colour(r, g, b);
        this->w = w;
        white(w);
    }
}
