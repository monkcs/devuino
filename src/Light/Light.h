#ifndef LIGHT_H
#define LIGHT_H

#include "Resolution.h"
#include <Arduino.h>

namespace devuino
{
    class Light
    {
      public:
        Light(int bitresolution);
        int brightness() const;
        void brightness(float percent);
        virtual void brightness(int value) = 0;

      protected:
        int bright = 0;
        const Resolution bitsize;
    };
}

#endif
