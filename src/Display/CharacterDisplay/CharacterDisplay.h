#ifndef CHARACTERDISPLAY_H
#define CHARACTERDISPLAY_H

#include "../Cursor.h"
#include "../Direction.h"
#include "../Display.h"
#include "../Vector2D.h"

namespace devuino
{
    template <typename TPosition, typename TCharacter>
    class CharacterDisplay : public Display<TPosition>
    {
      public:
        CharacterDisplay(const Vector2D<TPosition> dimension,
                         const Cursor<TCharacter, TPosition> cursor,
                         const Direction direction)
            : Display<TPosition>(dimension), cursor(cursor), direction(direction) {}

        Cursor<TCharacter, TPosition> cursor;

        Direction direction;

      protected:
        void move(const int distance = 1)
        {
            if (direction.flow == Direction::Primary::Horizontal)
            {
                cursor.x += (distance * static_cast<uint8_t>(direction.x));
            }
            else if (direction.flow == Direction::Primary::Vertical)
            {
                cursor.y += (distance * static_cast<uint8_t>(direction.y));
            }
        }
    };
}

#endif
