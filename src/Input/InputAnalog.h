#ifndef INPUTANALOG_H
#define INPUTANALOG_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class InputAnalog
    {
      public:
        InputAnalog(int bitresolution, bool debounce)
        : bitsize(bitresolution), debounce(debounce) {};

        double percent()
        {
            return (double)value() / (double)(bitsize.resolution - 1);
        };

        virtual int value() = 0;

      protected:
        const Resolution bitsize;
        const bool debounce;
    };
}

#endif
