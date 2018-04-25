#include "Rgbw.h"

void Rgbw::brightness(int value) {
    bright = value;
    color(r, g, b, w);
}

void Rgbw::color(long hexadecimal) {
    color((byte)(hexadecimal >> 32), (byte)(hexadecimal >> 16), (byte)(hexadecimal >> 8), (byte)(hexadecimal));
}

void Rgbw::color(byte r, byte g, byte b, byte w) {
    Rgb::color(r,g,b);
    this->w = w;
    white(w);
}