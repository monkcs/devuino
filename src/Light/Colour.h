#ifndef Colour_H
#define Colour_H

#include <stdint.h>

#include "../Tools/Iterator.h"
#include "Channel.h"

namespace devuino
{
    class Colour
    {
      public:
        constexpr Colour(const uint8_t red, const uint8_t green, const uint8_t blue)
            : red(red), green(green), blue(blue){};

        constexpr Colour()
            : Colour{0, 0, 0} {};

        constexpr Colour(const uint32_t hexadecimal)
            : Colour{
                  static_cast<uint8_t>(hexadecimal >> 16),
                  static_cast<uint8_t>(hexadecimal >> 8),
                  static_cast<uint8_t>(hexadecimal)} {};

        constexpr uint8_t operator[](const uint8_t index) const
        {
            return colours[index];
        };

        uint8_t& operator[](const uint8_t index)
        {
            return colours[index];
        };

        devuino::tools::Iterator<const uint8_t> begin() const
        {
            return {colours};
        }
        devuino::tools::Iterator<const uint8_t> end() const
        {
            return {colours + 3};
        }
        devuino::tools::Iterator<uint8_t> begin()
        {
            return {colours};
        }
        devuino::tools::Iterator<uint8_t> end()
        {
            return {colours + 3};
        }

        union
        {
            struct
            {
                uint8_t red;
                uint8_t green;
                uint8_t blue;
            };

            uint8_t colours[3];
        };
    };
}

#endif
