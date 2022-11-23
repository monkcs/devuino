#pragma once

#include "../../Iterator/Iterator.hpp"

#include <stdint.h>

namespace devuino::utilities
{

	class SevenSegmentCharacter
	{
		uint8_t character;

		constexpr uint8_t convert(const char character) const
		{
			if (character >= 32 && character <= 57)
			{
				switch (character)
				{
					case ' ': return 0x0;
					case '!': return 0x0;
					case '"': return 0x0;
					case '#': return 0x0;
					case '$': return 0x0;
					case '%': return 0x0;
					case '&': return 0x0;
					case '\'': return 0x0;
					case '(': return 0x0;
					case ')': return 0x0;
					case '*': return 0x0;
					case '+': return 0x0;
					case ',': return 0x0;
					case '-': return 0x01;
					case '.': return 0x80;
					case '/': return 0x0;
					case '0': return 0x7e;
					case '1': return 0x30;
					case '2': return 0x6d;
					case '3': return 0x79;
					case '4': return 0x33;
					case '5': return 0x5b;
					case '6': return 0x5f;
					case '7': return 0x70;
					case '8': return 0x7f;
					case '9': return 0x7b;

					default: return 0x0;
				}
			}
			else
			{
				return 0x0;
			}
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

		constexpr SevenSegmentCharacter& operator|=(const SevenSegmentCharacter& other)
		{
			character |= other.character;
			return *this;
		};
	};

	/* User defined litterals */
	constexpr SevenSegmentCharacter operator""_char7s(const char character) { return SevenSegmentCharacter {character}; }
}
