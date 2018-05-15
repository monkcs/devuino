#ifndef LIGHT_H
#define LIGHT_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class Light
    {
      public:
        int brightness();
        void brightness(float percent);
        virtual void brightness(int value) = 0;

      protected:
        int bright = 0;
        Resolution bitsize;
    };
}

#endif
