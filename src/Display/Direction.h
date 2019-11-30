#ifndef DIRECTION_H
#define DIRECTION_H

namespace devuino
{
    class Direction
    {
        public:
          enum class Horizontal : uint8_t
          {
              None,
              Left,
              Center,
              Right
          };

          enum class Vertical : uint8_t
          {
              None,
              Up,
              Center,
              Down
          };

          constexpr Direction(const Horizontal, const Vertical y) : x(x), y(y) {}

          Horizontal x;
          Vertical y;
    };
}

#endif
