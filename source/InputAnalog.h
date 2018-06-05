#ifndef INPUTANALOG_H
#define INPUTANALOG_H

#include "Resolution.h"

namespace devuino
{
    class InputAnalog
    {
      public:
        InputAnalog(int bitresolution, bool debounce = false);

        float percent();
        virtual int value() = 0;

      protected:
        Resolution bitsize;
        const bool debounce;
    };
}

#endif