#pragma once
#include "../../../Tools/Array.hpp"
#include "../../../Tools/Iterator.hpp"
#include "../../../Tools/Stringview.hpp"
#include "SevenSegmentCharacter.hpp"

#include <stdint.h>

namespace devuino
{
	template<size_t lenght>
	class SevenSegmentString : public tools::Array<SevenSegmentCharacter, lenght>
	{
	  public:
		constexpr SevenSegmentString() : devuino::tools::Array<SevenSegmentCharacter, lenght> {} { }

		SevenSegmentString(const tools::Stringview string)
		{
			/*
			   The constructor copy the characters from the stringview to SevenSegmentCharacters.
			   It checks if a dot '.' is present and then "merges" it to the previous character
			   in the buffer, as seven segment displays have a dedicated dot on each character.
			*/

			auto iterator_buffer = this->begin();
			auto iterator_string = string.begin();

			bool previously_merged = false;

			while (iterator_buffer != this->end() && iterator_string != string.end())
			{
				if (*iterator_string == '.' && previously_merged == false && iterator_buffer != this->begin())
				{
					iterator_buffer.previous() |= '.';
					previously_merged = true;
				}
				else
				{
					*iterator_buffer = *iterator_string;

					previously_merged = false;
					++iterator_buffer;
				}
				++iterator_string;
			}

			if (iterator_string != string.end())
			{
				if (*iterator_string == '.')
				{
					iterator_buffer.previous() |= '.';
				}
			}
		}

		constexpr explicit operator const SevenSegmentCharacter*() const { return this->buffer; }
		constexpr explicit operator SevenSegmentCharacter*() { return this->buffer; }

		SevenSegmentString& operator=(const tools::Stringview& string)
		{
			this->fill({});
			*this = SevenSegmentString {string};

			return *this;
		}

		/* Number of characters */
		constexpr size_t size() const { return lenght; }

		/* Bound checked index access, access outside string returns empty character */
		SevenSegmentCharacter at(const size_t position) const
		{
			return position < lenght ? this->buffer[position] : SevenSegmentCharacter {};
		}

		SevenSegmentCharacter operator[](const size_t position) const { return this->buffer[position]; }
		SevenSegmentCharacter& operator[](const size_t position) { return this->buffer[position]; }

		tools::Iterator<const SevenSegmentCharacter> begin() const { return {this->buffer}; }
		tools::Iterator<const SevenSegmentCharacter> end() const { return {this->buffer + lenght}; }
		tools::Iterator<SevenSegmentCharacter> begin() { return {this->buffer}; }
		tools::Iterator<SevenSegmentCharacter> end() { return {this->buffer + lenght}; }

		bool operator==(const SevenSegmentString<lenght>& other) const
		{
			for (size_t i = 0; i < lenght; i++)
			{
				if (this->buffer[i] != other.buffer[i])
				{
					return false;
				}
			}
			return true;
		}
		bool operator!=(const SevenSegmentString<lenght>& other) const { return !(this == other); }
	};
}