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
			switch (character)
			{
				case ' ': return 0x0;
				case '!': return 0x0;
				case '"': return 34;
				case '\'': return 32;
				case '(': return 0x0;
				case ')': return 0x0;
				case ',': return 0x80;
				case '-': return 0x01;
				case '.': return 0x80;
				case '/': return 0x0;
				case '_': return 0x8;
				case '=': return 0x9;

				case '0': return 0x7E;
				case '1': return 0x30;
				case '2': return 0x6D;
				case '3': return 0x79;
				case '4': return 0x33;
				case '5': return 0x5B;
				case '6': return 0x5F;
				case '7': return 0x70;
				case '8': return 0x7F;
				case '9': return 0x7B;
				case 'A': return 0x77;
				case 'a': return 0x7D;
				case 'B': return 0x7F;
				case 'b': return 0x1F;
				case 'C': return 0x4E;
				case 'c': return 0x0D;
				case 'D': return 0x7E;
				case 'd': return 0x3D;
				case 'E': return 0x4F;
				case 'e': return 0x6f;
				case 'F': return 0x47;
				case 'f': return 0x47;
				case 'G': return 0x5E;
				case 'g': return 0x7B;
				case 'H': return 0x37;
				case 'h': return 0x17;
				case 'I': return 0x30;
				case 'i': return 0x10;
				case 'J': return 0x3C;
				case 'j': return 0x38;
				case 'K': return 0x37;
				case 'k': return 0x17;
				case 'L': return 0x0E;
				case 'l': return 0x06;
				case 'M': return 0x55;
				case 'm': return 0x55;
				case 'N': return 0x15;
				case 'n': return 0x15;
				case 'O': return 0x7E;
				case 'o': return 0x1D;
				case 'P': return 0x67;
				case 'p': return 0x67;
				case 'Q': return 0x73;
				case 'q': return 0x73;
				case 'R': return 0x77;
				case 'r': return 0x05;
				case 'S': return 0x5B;
				case 's': return 0x5B;
				case 'T': return 0x46;
				case 't': return 0x0F;
				case 'U': return 0x3E;
				case 'u': return 0x1C;
				case 'V': return 0x27;
				case 'v': return 0x23;
				case 'W': return 0x3F;
				case 'w': return 0x2B;
				case 'X': return 0x25;
				case 'x': return 0x25;
				case 'Y': return 0x3B;
				case 'y': return 0x33;
				case 'Z': return 0x6D;
				case 'z': return 0x6D;

				default: return 0x0;
			}
		};

	  public:
		constexpr SevenSegmentCharacter() : character {0} {};

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
	constexpr SevenSegmentCharacter operator""_char7s(const char character) { return character; }
	constexpr SevenSegmentCharacter operator""_char7s_raw(const char character) { return SevenSegmentCharacter {character, true}; }
}
