#pragma once
#include "Iterator.hpp"
#include "String.hpp"

namespace devuino::tools
{
	class Stringview
	{
	  private:
		size_t size;
		const char* backend;

		constexpr size_t calculate(const char* string) const { return (*string) ? (1 + calculate(string + 1)) : 0; }

	  public:
		/* Construct stringview to a raw char array that is null-terminated */
		constexpr Stringview(const char* raw) : size {calculate(raw)}, backend {raw} { }

		/* Construct string from raw char array where lenght is exclusive null-terminator */
		constexpr Stringview(const char* raw, const size_t lenght) : size {lenght}, backend {raw} { }

		constexpr Stringview(const Stringview& other) : size {other.size}, backend {other.backend} { }

		constexpr Stringview(const String& other) : size {other.size}, backend {other.buffer} { }

		Stringview& operator=(const Stringview& other)
		{
			size = other.size;
			backend = other.backend;

			return *this;
		}

		Stringview& operator=(const String& other)
		{
			size = other.size;
			backend = other.buffer;

			return *this;
		}

		constexpr explicit operator const char*() const { return backend; }

		/* Lenght of string exclusive null-terminator */
		constexpr size_t lenght() const { return size; }

		/* Bound checked index access */
		constexpr char at(const size_t position) const { return position < lenght() ? backend[position] : '\0'; }

		char operator[](const size_t position) const { return backend[position]; }

		Iterator<const char> begin() const { return {backend}; }
		Iterator<const char> end() const { return {backend + size}; }

		friend bool operator==(const Stringview& lhs, const Stringview& rhs)
		{
			if (lhs.size == rhs.size)
			{
				for (size_t i; i < lhs.size; i++)
				{
					if (lhs.backend[i] != rhs.backend[i])
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
		friend bool operator!=(const Stringview& lhs, const Stringview& rhs) { return !(lhs == rhs); }
	};

	constexpr Stringview operator"" _sv(const char* const raw, const size_t i) { return Stringview {raw, i}; }
}