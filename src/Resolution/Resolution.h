#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution final
    {
        public:

            /* Set the bits and compute the resolution with a cap on 15 bits,
             * (because currently we are using a uint16_t int to hold it. */

            constexpr Resolution(const uint8_t bits)
                : bits((bits < 15) ? bits : 15),
                  resolution(1u << (bits < 15) ? bits : 15),
                  range(0, resolution - 1)
            { };

            const uint8_t bits;
            const uint16_t resolution;

            struct Range final
            {
                constexpr Range(const uint8_t minimum, const uint16_t maximum)
                    : minimum(minimum), maximum(maximum)
                { };

                const uint8_t minimum;
                const uint16_t maximum;
            } const range;

    };
}

#endif
