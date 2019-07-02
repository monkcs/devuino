#include "Rgbw.h"

namespace devuino
{
    void Rgbw::brightness(const int value)


    void Rgbw::colour(const uint32_t hexadecimal) const


    void Rgbw::colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t w)
    {
        Rgb::colour(r, g, b);
        this->w = w;
        white(w);
    }
}
