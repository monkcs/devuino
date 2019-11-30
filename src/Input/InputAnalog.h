#ifndef INPUTANALOG_H
#define INPUTANALOG_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class InputAnalog
    {
      public:
        InputAnalog(const uint8_t bitresolution, const bool debounce)
        : bitsize(bitresolution), debounce(debounce) {};

        double percent() const
        {
            return static_cast<double>(value()) / static_cast<double>(bitsize.maximum());
        };

        virtual int value() = 0;

      protected:
        const Resolution bitsize;
        const bool debounce;
    };
}

#endif
