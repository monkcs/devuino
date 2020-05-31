#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution final
    {
        public:

            /* Set the bits and compute the resolution with a cap on 15 bits,
             * (because currently we are using a uint16_t int to return it. */

            explicit constexpr Resolution(const uint8_t bits) : bitresolution((bits < 15) ? bits : 15)
            { };

            constexpr uint8_t bits() const
            {
                return bitresolution;
            };

            constexpr uint16_t resolution() const
            {
                return 1 << bitresolution;
            };

            constexpr uint8_t minimum() const
            {
                return 0;
            };

            constexpr uint16_t maximum() const
            {
                return (1 << bitresolution) - 1;
            };

        private:
            const uint8_t bitresolution;
    };
}

#endif
