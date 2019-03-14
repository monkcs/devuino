#ifndef LIGHT_H
#define LIGHT_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class Light
    {
        public:
            Light(const int bitresolution)
                : bitsize(bitresolution)
            {
            };

            int brightness() const
            {
                return bright;
            };

            void brightness(const double percent) const
            {
                brightness((int)((bitsize.resolution - 1) * percent));
            };

            virtual void brightness(const int value) = 0;

        protected:
            int bright = 0;
            const Resolution bitsize;
    };
}

#endif
