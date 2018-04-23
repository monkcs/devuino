#include "Rgb.h"

void Rgb::brightness(byte value) {
    bright = value;
    color(r, g, b);
}
void Rgb::color(long hexadecimal) {
    color((byte)(hexadecimal >> 16), (byte)(hexadecimal >> 8), (byte)(hexadecimal));
}

void Rgb::color(byte r, byte g, byte b) {
    this->r = r;
    this->g = g;
    this->b = b;
    red(r);
    green(g);
    blue(b);
}