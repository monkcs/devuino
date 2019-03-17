#include "Rgbw.h"

namespace devuino
{
    void Rgbw::brightness(const int value)
    {
        bright = value;
        colour(r, g, b, w);
    }

    void Rgbw::colour(const uint32_t hexadecimal) const
    {
        colour((uint8_t)(hexadecimal >> 24), (uint8_t)(hexadecimal >> 16), (uint8_t)(hexadecimal >> 8), (uint8_t)(hexadecimal));
    }

    void Rgbw::colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t w)
    {
        Rgb::colour(r, g, b);
        this->w = w;
        white(w);
    }
}
