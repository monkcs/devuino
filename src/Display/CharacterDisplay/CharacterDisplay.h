#pragma once

#include "../Cursor.hpp"
#include "../Direction.hpp"
#include "../Display.hpp"
#include "../Vector2D.hpp"

namespace devuino
{
	template<typename Position, typename Character>
	class CharacterDisplay : public Display<Position>
	{
	  public:
		CharacterDisplay(const Vector2D<Position> dimension, const Cursor<Character, Position> cursor, const Direction direction) :
			Display<Position> {dimension}, cursor {cursor}, direction {direction} {};

		Cursor<Character, Position> cursor;
		Direction direction;

	  protected:
		void move(const int distance = 1)
		{
			if (direction.flow == Direction::Primary::Horizontal)
			{
				switch (direction.x)
				{
					case Direction::Horizontal::Left:
					{
						cursor.x += distance;
						break;
					}

					case Direction::Horizontal::Right:
					{
						cursor.x -= distance;
						break;
					}

					default:
					{
						break;
					}
				}
			}
			else if (direction.flow == Direction::Primary::Vertical)
			{
				switch (direction.y)
				{
					case Direction::Vertical::Up:
					{
						cursor.y += distance;
						break;
					}

					case Direction::Vertical::Down:
					{
						cursor.y -= distance;
						break;
					}

					default:
					{
						break;
					}
				}
			}
		}
	};
}
