#ifndef CHARACTERDISPLAY_H
#define CHARACTERDISPLAY_H

#include "../Cursor.h"
#include "../Direction.h"
#include "../Vector2D.h"
#include "../Display.h"

namespace devuino
{
    template <typename TPosition, typename TCharacter>
    class CharacterDisplay : public Display<TPosition>
    {
        public:
          CharacterDisplay(const Vector2D<TPosition> dimension,
                           const Cursor<TCharacter, TPosition> cursor,
                           const Direction direction)
            : Display<TPosition>(dimension), cursor(cursor), direction(direction)  {}

        protected:
          Cursor<TCharacter, TPosition> cursor;
          Direction direction;
    };
}

#endif