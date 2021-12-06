#pragma once
#include "Iterator.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace devuino::tools
{
	class String
	{
		friend class Stringview;

	  private:
		size_t size;
		char* buffer;

	  public:
		/* Construct string from raw char */
		explicit String(const char raw) : size {2}, buffer {new char[size]}
		{
			buffer[0] = raw;
			buffer[1] = '\0';
		}

		/* Construct string from raw char array that is null-terminated */
		String(const char raw[]) : size {strlen(raw) + 1}, buffer {new char[size]} { memcpy(buffer, raw, size); }

		/* Construct string from raw char array where lenght is exclusive null-terminator */
		String(const char raw[], const size_t lenght) : size {lenght + 1}, buffer {new char[size]}
		{
			memcpy(buffer, raw, lenght);
			buffer[size - 1] = '\0';
		}

		String(const String& other) : size {other.size}
		{
			buffer = new char[size];
			memcpy(buffer, other.buffer, size);
		}

		~String() { delete[] buffer; }

		String& operator=(const String& other)
		{
			delete[] buffer;

			size = other.size;
			buffer = new char[size];
			memcpy(buffer, other.buffer, other.size);

			return *this;
		}

		constexpr explicit operator const char*() const { return buffer; }
		constexpr explicit operator char*() { return buffer; }

		/* Lenght of string exclusive null-terminator */
		constexpr size_t lenght() const { return size - 1; }

		/* Append to the string */
		String& operator+=(const String& other)
		{
			const auto combined = size + other.size - 1;

			const auto concatenated = new char[combined];
			memcpy(concatenated, buffer, size);
			memcpy(&concatenated[size - 1], other.buffer, other.size);

			size = combined;

			delete[] buffer;
			buffer = concatenated;

			return *this;
		}

		/* Bound checked index access */
		char at(const size_t position) const { return position < lenght() ? buffer[position] : '\0'; }

		char operator[](const size_t position) const { return buffer[position]; }
		char& operator[](const size_t position) { return buffer[position]; }

		Iterator<const char> begin() const { return {buffer}; }
		Iterator<const char> end() const { return {buffer + size}; }
		Iterator<char> begin() { return {buffer}; }
		Iterator<char> end() { return {buffer + size}; }

		friend String operator+(const String& lhs, const String& rhs)
		{
			String result {lhs};
			result += rhs;

			return result;
		}

		friend bool operator==(const String& lhs, const String& rhs)
		{
			if (lhs.size == rhs.size)
			{
				for (size_t i = 0; i < lhs.size; i++)
				{
					if (lhs.buffer[i] != rhs.buffer[i])
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		friend bool operator!=(const String& lhs, const String& rhs) { return !(lhs == rhs); }
	};

	String operator"" _s(const char* const raw, const size_t i) { return String {raw, i}; }
}
