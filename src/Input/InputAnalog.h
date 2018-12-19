#ifndef INPUTANALOG_H
#define INPUTANALOG_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class InputAnalog
    {
      public:
        InputAnalog(int bitresolution, bool debounce);

        float percent();
        virtual int value() = 0;

      protected:
        const Resolution bitsize;
        const bool debounce;
    };
}

#endif