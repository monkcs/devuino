#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <stdint.h>

namespace devuino
{
    class Resolution final
    {
      public:
        /* Set the bits and compute the resolution with a cap on 15 bits,
           (because currently we are using a uint16_t int to return it. */

        explicit constexpr Resolution(const uint8_t bit)
            : bits((bit < 15) ? bit : 15),
              maximum((1 << ((bit < 15) ? bit : 15)) - 1){};

        const uint8_t bits;
        const uint16_t maximum;
    };
}

#endif
