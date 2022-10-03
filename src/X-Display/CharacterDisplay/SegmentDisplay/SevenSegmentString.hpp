#pragma once
#include "../../../Tools/Array.hpp"
#include "../../../Tools/Iterator.hpp"
#include "../../../Tools/Stringview.hpp"
#include "SevenSegmentCharacter.hpp"

#include <stdint.h>

namespace devuino
{
	using devuino::tools::Array;
	using devuino::tools::Iterator;
	using devuino::tools::Stringview;

	template<size_t lenght>
	class SevenSegmentString : public Array<SevenSegmentCharacter, lenght>
	{
		static_assert(lenght > 0, "Lenght of SevenSegmentString cannot be zero");

	  public:
		SevenSegmentString() = default;
		SevenSegmentString(const Stringview string)
		{
			/*
			   The constructor copy the characters from the stringview to SevenSegmentCharacters.
			   It checks if a dot '.' is present and then "merges" it to the previous character
			   in the buffer, as seven segment displays have a dedicated dot on each character.
			*/

			if (string.empty())
			{
				return;
			}
			else
			{
				bool previously_merged = false;

				/* Test if the first character is '.', as it cannot be merged with the previous character */
				if (string.front() == '.')
				{
					previously_merged = true;
				}

				auto iterator_buffer = this->begin();
				auto iterator_string = string.begin();

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

				if (iterator_buffer != this->end())
				{
					*iterator_buffer = '\0';
				}
			}
		}

		SevenSegmentString& operator=(const Stringview& string)
		{
			*this = SevenSegmentString {string};
			return *this;
		}

		/* Clear the array */
		void clear() { this->fill('\0'); }

		/* Bound checked index access, access outside string returns empty character */
		constexpr SevenSegmentCharacter at(const size_t position) const
		{
			return position < lenght ? this->buffer[position] : SevenSegmentCharacter {};
		}

		SevenSegmentCharacter operator[](const size_t position) const { return this->buffer[position]; }
		SevenSegmentCharacter& operator[](const size_t position) { return this->buffer[position]; }

		bool operator==(const SevenSegmentString<lenght>& other) const
		{
			return equals(static_cast<Array<SevenSegmentCharacter, lenght>>(other));
		}
		bool operator!=(const SevenSegmentString<lenght>& other) const { return !(this == other); }
	};
}