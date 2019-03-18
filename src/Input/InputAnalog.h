#ifndef INPUTANALOG_H
#define INPUTANALOG_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class InputAnalog
    {
      public:
        InputAnalog(const int bitresolution, const bool debounce)
        : bitsize(bitresolution), debounce(debounce) {};

        double percent() const
        {
            return static_cast<double>(value()) / static_cast<double>(bitsize.resolution - 1);
        };

        virtual int value() = 0;

      protected:
        const Resolution bitsize;
        const bool debounce;
    };
}

#endif
