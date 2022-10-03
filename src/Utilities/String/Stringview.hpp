#pragma once
#include "../Iterator/Iterator.hpp"
#include "String.hpp"

#include <stdint.h>

namespace devuino::utilities
{
	class Stringview
	{
		size_t size;
		const char* backend;

		/* Calculates string lenght exclusive null-terminator */
		constexpr static size_t calculate(const char* string) { return (*string) ? (1 + calculate(string + 1)) : 0; }

	  public:
		/* Construct stringview to a raw char array that is null-terminated */
		constexpr Stringview(const char* raw) : size {calculate(raw)}, backend {raw} { }

		/* Construct stringview to a raw char array where lenght is exclusive null-terminator */
		constexpr Stringview(const char* raw, const size_t lenght) : size {lenght}, backend {raw} { }

		Stringview(const Stringview&) = default;
		Stringview(Stringview&&) = default;

		constexpr Stringview(const String& other) : size {other.size}, backend {other.buffer} { }

		Stringview& operator=(const Stringview&) = default;
		Stringview& operator=(Stringview&&) = default;

		/* Underlying raw char* from the owning String */
		constexpr explicit operator const char*() const { return backend; }

		/* Lenght of string exclusive null-terminator */
		constexpr size_t lenght() const { return size; }

		constexpr bool empty() const { return size == 0; }

		/* Bound checked index access */
		constexpr char at(const size_t position) const { return position < lenght() ? backend[position] : '\0'; }

		char operator[](const size_t position) const { return backend[position]; }

		constexpr char front() const { return backend[0]; }
		constexpr char back() const { return backend[(size > 0) ? (size - 1) : 0]; }

		Iterator<const char> begin() const { return {backend}; }
		Iterator<const char> end() const { return {backend + size}; }

		friend bool operator==(const Stringview& lhs, const Stringview& rhs)
		{
			if (lhs.size == rhs.size)
			{
				for (size_t i = 0; i < lhs.size; i++)
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