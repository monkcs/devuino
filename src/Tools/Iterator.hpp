#pragma once

/* https://www.nextptr.com/tutorial/ta1208652092/how-cplusplus-rangebased-for-loop-works */

namespace devuino::tools
{
	template<typename T>
	class Iterator final
	{
	  public:
		T* pointer;

		constexpr T& operator*() { return *pointer; };
		constexpr bool operator!=(const Iterator& rhs) const { return pointer != rhs.pointer; };
		void operator++() { ++pointer; };
	};
}
