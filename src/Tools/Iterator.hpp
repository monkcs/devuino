#pragma once

/* https://www.nextptr.com/tutorial/ta1208652092/how-cplusplus-rangebased-for-loop-works */

namespace devuino::tools
{
	template<typename Type>
	class Iterator final
	{
	  public:
		Type* pointer;

		constexpr Type& operator*() { return *pointer; };
		constexpr Type& next() { return *(pointer + 1); };
		constexpr Type& previous() { return *(pointer - 1); };
		constexpr bool operator!=(const Iterator& rhs) const { return pointer != rhs.pointer; };
		void operator++() { ++pointer; };
		void operator--() { --pointer; };
	};
}
