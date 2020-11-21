#ifndef LIGHT_H
#define LIGHT_H

#include "../Resolution/Resolution.h"

namespace devuino
{
    class Light
    {
      public:
        constexpr Light(const Resolution bitresolution)
            : bitsize(bitresolution), bright(bitresolution.maximum){};

        virtual unsigned int brightness() const = 0;
        virtual void brightness(const unsigned int value) = 0;

        void percent(const double percent)
        {
            brightness(static_cast<unsigned int>(bitsize.maximum * percent));
        };

      protected:
        const Resolution bitsize;
        unsigned int bright;
    };
}

#endif
