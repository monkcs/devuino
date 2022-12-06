#pragma once
#include "../../Array/Array.hpp"
#include "../../Iterator/Iterator.hpp"
#include "../../String/Stringview.hpp"
#include "SevenSegmentCharacter.hpp"

#include <stdint.h>

namespace devuino::utilities
{
	using devuino::utilities::Array;
	using devuino::utilities::Iterator;
	using devuino::utilities::Stringview;

	enum class SevenSegmentStringLayout
	{
		FirstCharacterFirst,
		FirstCharacterLast
	};

	/// @brief Fixed size string of SevenSegmentCharacter
	/// @tparam lenght Lenght of string
	/// @tparam MSB Character layout order
	template<size_t lenght, bool MSB = true>
	class SevenSegmentString : public Array<SevenSegmentCharacter, lenght>
	{
		static_assert(lenght > 0, "Lenght of SevenSegmentString cannot be zero");
		using Layout = SevenSegmentStringLayout;

	  public:
		SevenSegmentString() = default;
		constexpr SevenSegmentString(const char character)
		{
			if (MSB)
			{
				this->front() = character;
			}
			else
			{
				this->back() = character;
			}
		}
		constexpr SevenSegmentString(const Stringview string)
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

				if (MSB == true)
				{
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
				}
				else
				{
					auto iterator_buffer = this->rbegin();
					auto iterator_string = string.begin();

					*iterator_buffer = *iterator_string;
					++iterator_buffer;
					++iterator_string;

					while (iterator_buffer != this->rend() && iterator_string != string.end())
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
			}
		}

		constexpr SevenSegmentString& operator=(const Stringview& string)
		{
			*this = SevenSegmentString {string};
			return *this;
		}

		/// @brief Clear the array
		constexpr void clear() { this->fill(SevenSegmentCharacter {}); }

		/// @brief Bound checked index access
		/// @param position Position of character
		/// @return Character at position, access outside string return empty character
		constexpr SevenSegmentCharacter at(const size_t position) const
		{
			return position < lenght ? this->buffer[position] : SevenSegmentCharacter {};
		}

		constexpr SevenSegmentCharacter operator[](const size_t position) const { return this->buffer[position]; }
		constexpr SevenSegmentCharacter& operator[](const size_t position) { return this->buffer[position]; }

		constexpr bool operator==(const SevenSegmentString<lenght>& other) const
		{
			return this->equals(static_cast<Array<SevenSegmentCharacter, lenght>>(other));
		}
		constexpr bool operator!=(const SevenSegmentString<lenght>& other) const { return !operator==(other); }
	};
}