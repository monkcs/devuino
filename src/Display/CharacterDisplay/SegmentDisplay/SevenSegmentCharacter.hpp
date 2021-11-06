#pragma once

#include "../../../Tools/Iterator.hpp"
#include "../CharacterDisplay.h"

namespace devuino
{
	static constexpr uint8_t table[] = {
		0x0,	 // ' '
		0x0,	 // !
		0x0,	 // "
		0x0,	 // #
		0x0,	 // $
		0x0,	 // %
		0x0,	 // &
		0x0,	 // '
		0x0,	 // (
		0x0,	 // )
		0x0,	 // *
		0x0,	 // +
		0x0,	 // ,
		0x01,	 // -
		0x80,	 // .
		0x0,	 // /
		0x7e,	 // 0
		0x30,	 // 1
		0x6d,	 // 2
		0x79,	 // 3
		0x33,	 // 4
		0x5b,	 // 5
		0x5f,	 // 6
		0x70,	 // 7
		0x7f,	 // 8
		0x7b,	 // 9

		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
		0x0,	//
	};

	class SevenSegmentCharacter
	{
	  public:
		constexpr SevenSegmentCharacter(const char character) : character {convert(character)} {};
		constexpr SevenSegmentCharacter(const int digit) : character {convert(digit)} {};

		constexpr SevenSegmentCharacter() : character {0x0} {};

		constexpr operator uint8_t() const { return character; };

	  private:
		uint8_t character;

		constexpr uint8_t convert(const char character) const
		{
			return (character >= 32 && character <= 126) ? table[character - 32] : 0x0;
		};
		constexpr uint8_t convert(const int number) const { return (number >= 0 && number < 10) ? table[number + 16] : 0x0; };
	};

	/* User defined litterals */
	constexpr SevenSegmentCharacter operator""_char7s(const unsigned long long int character)
	{
		return SevenSegmentCharacter {static_cast<int>(character)};
	}
	constexpr SevenSegmentCharacter operator""_char7s(const char character) { return SevenSegmentCharacter {character}; }
}
