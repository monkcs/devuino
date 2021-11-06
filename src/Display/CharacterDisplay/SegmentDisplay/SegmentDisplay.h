#pragma once

#include "../../../Tools/Iterator.hpp"
#include "../CharacterDisplay.h"
#include "SevenSegmentCharacter.hpp"

namespace devuino
{
	template<typename T>
	class SevenSegmentString
	{
	  public:
		constexpr uint8_t count(const unsigned long int number) const { return ((number == 0) ? 0 : (1 + count(number / 10))); };

		explicit SevenSegmentString(int number)
		{
			size_t cursor = 0;

			if (number < 0)
			{
				number = -number;

				string[0] = '-';
				cursor += 1;
			}

			const auto lenght = count(number);

			for (cursor += lenght - 1; cursor >= 0; cursor--)
			{
				if (number == 0)
				{
					break;
				}

				string[cursor] = number % 10;
				number /= 10;
			}
		};

		devuino::tools::Iterator<const SevenSegmentCharacter> begin() const { return {string}; }
		devuino::tools::Iterator<const SevenSegmentCharacter> end() const { return {string + 6}; }
		devuino::tools::Iterator<SevenSegmentCharacter> begin() { return {string}; }
		devuino::tools::Iterator<SevenSegmentCharacter> end() { return {string + 6}; }

		SevenSegmentCharacter string[6] {};	   // Calculates number of char for int + null terminator
	};

	template<typename Position, typename Character>
	class SegmentDisplay : public CharacterDisplay<Position, Character>
	{
	  public:
		SegmentDisplay(const Vector2D<Position> dimension, const Cursor<Character, Position> cursor, const Direction direction) :
			CharacterDisplay<Position, Character>(dimension, cursor, direction)
		{
		}

		// virtual constexpr void print(TCharacter number) = 0;
	  protected:
	};
}
