#pragma once
#include "../../../Tools/Array.hpp"
#include "../../../Tools/Iterator.hpp"
#include "../../../Tools/Stringview.hpp"
#include "SevenSegmentCharacter.hpp"

#include <stdint.h>

namespace devuino
{
	template<size_t lenght>
	class SevenSegmentString : protected tools::Array<SevenSegmentCharacter, lenght>
	{
	  public:
		constexpr SevenSegmentString() : devuino::tools::Array<SevenSegmentCharacter, lenght> {} { }

		SevenSegmentString(const tools::Stringview& string) { parse(string); }

		constexpr explicit operator const SevenSegmentCharacter*() const { return this->buffer; }
		constexpr explicit operator SevenSegmentCharacter*() { return this->buffer; }

		SevenSegmentString& operator=(const tools::Stringview& string)
		{
			for (auto& character : this->buffer)
			{
				character = {};
			}

			parse(string);

			return *this;
		}

		/* Number of elements */
		constexpr size_t size() const { return lenght; }

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

	  protected:
		void parse(const tools::Stringview& string)
		{
			auto iterator_buffer = this->begin();
			auto iterator_string = string.begin();

			bool previous = false;

			while (iterator_buffer != this->end() && iterator_string != string.end())
			{
				if (*iterator_string == '.' && previous == false && iterator_buffer != this->begin())
				{
					const char character = SevenSegmentCharacter {iterator_string.previous()} | 0x80;
					iterator_buffer.previous() = {character, true};
					previous = true;
				}
				else
				{
					*iterator_buffer = *iterator_string;

					previous = false;
					++iterator_buffer;
				}
				++iterator_string;
			}

			if (iterator_string != string.end())
			{
				if (*iterator_string == '.')
				{
					const char character = SevenSegmentCharacter {iterator_string.previous()} | 0x80;
					iterator_buffer.previous() = {character, true};
				}
			}
		}
	};
}