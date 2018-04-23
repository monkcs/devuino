#ifndef RGB_H
#define RGB_H

#include "../Light.h"

class Rgb : public Light  {
	public:
        void brightness(byte value);
        void color(long hexadecimal);
        void color(byte r, byte g, byte b);
		virtual void red(byte value) = 0;
        virtual void green(byte value) = 0;
        virtual void blue(byte value) = 0;
    protected:
        byte r, g, b = 0;
};

#endif
