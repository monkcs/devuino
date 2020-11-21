#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint.h>

namespace devuino
{
    class Channel
    {
      public:
        constexpr Channel(const uint8_t value)
            : value(value){};

        constexpr operator uint8_t() const
        {
            return value;
        };

      protected:
        const uint8_t value;
    };

    class Red : public Channel
    {
      public:
        explicit constexpr Red(const uint8_t value)
            : Channel(value){};

        constexpr operator uint8_t() const
        {
            return value;
        };
    };

    class Green : public Channel
    {
      public:
        explicit constexpr Green(const uint8_t value)
            : Channel(value){};

        constexpr operator uint8_t() const
        {
            return value;
        };
    };

    class Blue : public Channel
    {
      public:
        explicit constexpr Blue(const uint8_t value)
            : Channel(value){};

        constexpr operator uint8_t() const
        {
            return value;
        };
    };

    constexpr Red operator""_red(const unsigned long long int value)
    {
        return Red{static_cast<uint8_t>(value)};
    };
    constexpr Green operator""_green(const unsigned long long int value)
    {
        return Green{static_cast<uint8_t>(value)};
    };
    constexpr Blue operator""_blue(const unsigned long long int value)
    {
        return Blue{static_cast<uint8_t>(value)};
    };
}
#endif
