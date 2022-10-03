#pragma once

#include "../../../Tools/Iterator.hpp"

namespace devuino
{
	static const constexpr uint8_t table[] = {
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
		uint8_t character {};

		constexpr uint8_t convert(const char character) const
		{
			return (character >= 32 && character <= 126) ? table[character - 32] : 0x0;
		};

	  public:
		SevenSegmentCharacter() = default;

		constexpr SevenSegmentCharacter(const char character, const bool raw = false) :
			character {raw ? static_cast<uint8_t>(character) : convert(character)} {};

		constexpr explicit operator uint8_t() const { return character; };

		constexpr bool operator==(const SevenSegmentCharacter& other) const { return character == other.character; }
		constexpr bool operator!=(const SevenSegmentCharacter& other) const { return character != other.character; }

		constexpr SevenSegmentCharacter operator|(const SevenSegmentCharacter& other) const
		{
			return SevenSegmentCharacter {static_cast<char>(character | other.character), true};
		};

		SevenSegmentCharacter& operator|=(const SevenSegmentCharacter& other)
		{
			character |= other.character;
			return *this;
		};
	};

	/* User defined litterals */
	constexpr SevenSegmentCharacter operator""_char7s(const char character) { return SevenSegmentCharacter {character}; }
}
