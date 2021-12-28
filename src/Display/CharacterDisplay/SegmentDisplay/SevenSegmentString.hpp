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
		constexpr SevenSegmentString() { }

		SevenSegmentString(const tools::Stringview string)
		{
			/*
			   The constructor copy the characters from the stringview to SevenSegmentCharacters.
			   It checks if a dot '.' is present and then "merges" it to the previous character
			   in the buffer, as seven segment displays have a dedicated dot on each character.
			*/

			static_assert(lenght > 0, "Lenght of SevenSegmentString cannot be zero");
			if (string.lenght() == 0)
			{
				return;
			}

			auto iterator_buffer = this->begin();
			auto iterator_string = string.begin();

			bool previously_merged = false;

			/* Test if the first character is '.', as it cannot be merged with the previous character */
			if (*iterator_string == '.')
			{
				previously_merged = true;
			}

			*iterator_buffer = *iterator_string;
			++iterator_buffer;
			++iterator_string;

			while (iterator_buffer != this->end() && iterator_string != string.end())
			{
				if (*iterator_string == '.' && previously_merged == false)
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

			/* Even if iterator_buffer is at end, a last '.' can be merged on the last character */
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

		/* Bound checked index access, access outside string returns empty character */
		SevenSegmentCharacter at(const size_t position) const
		{
			return position < lenght ? this->buffer[position] : SevenSegmentCharacter {};
		}

		SevenSegmentCharacter operator[](const size_t position) const { return this->buffer[position]; }
		SevenSegmentCharacter& operator[](const size_t position) { return this->buffer[position]; }

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