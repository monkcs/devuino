#pragma once

/* https://www.nextptr.com/tutorial/ta1208652092/how-cplusplus-rangebased-for-loop-works */

namespace devuino::utilities
{
	template<typename Type>
	class Iterator
	{
	  public:
		Type* pointer;

		constexpr Type& operator*() { return *pointer; }
		constexpr Type& next() { return *(pointer + 1); }
		constexpr Type& previous() { return *(pointer - 1); }

		constexpr bool operator==(const Iterator& rhs) const { return pointer == rhs.pointer; }
		constexpr bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }

		constexpr void operator++() { ++pointer; }
		constexpr void operator--() { --pointer; }
	};

	template<typename Type>
	class ReverseIterator
	{
	  public:
		Type* pointer;

		constexpr Type& operator*() { return *pointer; }
		constexpr Type& next() { return *(pointer - 1); }
		constexpr Type& previous() { return *(pointer + 1); }

		constexpr bool operator==(const ReverseIterator& rhs) const { return pointer == rhs.pointer; }
		constexpr bool operator!=(const ReverseIterator& rhs) const { return !operator==(rhs); }

		constexpr void operator++() { --pointer; }
		constexpr void operator--() { ++pointer; }
	};
}
