#pragma once

#include "../Iterator/Iterator.hpp"

#include <stdlib.h>

namespace devuino::utilities
{
	template<class Type, size_t lenght>
	struct Array
	{
		static_assert(lenght > 0, "Lenght of Array cannot be zero");

		Type buffer[lenght];

		constexpr explicit operator const Type*() const { return buffer; }
		constexpr explicit operator Type*() { return buffer; }

		/* Number of elements */
		constexpr size_t size() const { return lenght; }

		constexpr Type operator[](const size_t position) const { return buffer[position]; }
		constexpr Type& operator[](const size_t position) { return buffer[position]; }

		/* Fill the array with specified value */
		constexpr void fill(const Type object)
		{
			for (auto& item : buffer)
			{
				item = object;
			}
		}

		constexpr void swap(Array<Type, lenght>& other)
		{
			for (size_t i {}; i < lenght; ++i)
			{
				const Type temporary {other[i]};
				other[i] = buffer[i];
				buffer[i] = temporary;
			}
		}

		constexpr Type front() const { return buffer[0]; }
		constexpr Type& front() { return buffer[0]; }

		constexpr Type back() const { return buffer[lenght - 1]; }
		constexpr Type& back() { return buffer[lenght - 1]; }

		constexpr Iterator<const Type> begin() const { return {buffer}; }
		constexpr Iterator<const Type> end() const { return {buffer + lenght}; }
		constexpr Iterator<Type> begin() { return {buffer}; }
		constexpr Iterator<Type> end() { return {buffer + lenght}; }

		constexpr ReverseIterator<const Type> rbegin() const { return {buffer + lenght - 1}; }
		constexpr ReverseIterator<const Type> rend() const { return {buffer - 1}; }
		constexpr ReverseIterator<Type> rbegin() { return {buffer + lenght - 1}; }
		constexpr ReverseIterator<Type> rend() { return {buffer - 1}; }

		constexpr bool operator==(const Array<Type, lenght>& other) const { return equals(other); }
		constexpr bool operator!=(const Array<Type, lenght>& other) const { return !operator==(other); }

	  protected:
		constexpr bool equals(const Array<Type, lenght>& other) const
		{
			for (size_t index {}; index < lenght; ++index)
			{
				if (buffer[index] != other.buffer[index])
				{
					return false;
				}
			}
			return true;
		}
	};
}
