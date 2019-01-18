#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution final
    {
        public:
            constexpr Resolution(unsigned int bits)
                : bits(bits), resolution(1u << bits)
            {
            };

            const unsigned int bits;
            const unsigned int resolution;
    };
}

#endif
