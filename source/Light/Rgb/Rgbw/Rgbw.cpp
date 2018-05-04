#include "Rgbw.h"

void Rgbw::brightness(int value)
{
    bright = value;
    colour(r, g, b, w);
}

void Rgbw::colour(long hexadecimal)
{
    colour((byte)(hexadecimal >> 32), (byte)(hexadecimal >> 16), (byte)(hexadecimal >> 8), (byte)(hexadecimal));
}

void Rgbw::colour(byte r, byte g, byte b, byte w)
{
    Rgb::colour(r, g, b);
    this->w = w;
    white(w);
}