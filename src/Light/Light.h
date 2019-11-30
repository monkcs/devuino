#ifndef LIGHT_H
#define LIGHT_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class Light
    {
        public:
            constexpr Light(const unsigned int bitresolution)
                : bitsize(bitresolution)
            {
            };

            virtual unsigned int brightness() const = 0;

            void percent(const double percent) const
            {
                brightness(static_cast<int>(bitsize.maximum() * percent));
            };

            virtual void brightness(const unsigned int value) = 0;

        protected:
            int bright = 0;
            const Resolution bitsize;
    };
}

#endif
