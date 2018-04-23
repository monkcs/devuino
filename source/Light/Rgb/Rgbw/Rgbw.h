#ifndef RGBW_H
#define RGBW_H

#include "../Rgb.h"

class Rgbw : public Rgb {
    public:
        void brightness(byte value);
        void color(long hexadecimal);
        void color(byte red, byte green, byte blue, byte white);
        virtual void white(byte value) = 0;
    protected:
        byte w = 0;
};

#endif