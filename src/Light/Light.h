#ifndef LIGHT_H
#define LIGHT_H

#include "../Resolution/Resolution.h"
#include <Arduino.h>

namespace devuino
{
    class Light
    {
        public:
            Light(int bitresolution)
                : bitsize(bitresolution)
            {
            };

            int brightness() const
            {
                return bright;
            };

            void brightness(float percent)
            {
                brightness((int)((bitsize.resolution - 1) * percent));
            };

            virtual void brightness(int value) = 0;

        protected:
            int bright = 0;
            const Resolution bitsize;
    };
}

#endif
