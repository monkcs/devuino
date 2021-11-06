#pragma once

#include "Vector2D.hpp"

namespace devuino
{
	template<typename T>
	class Display
	{
	  public:
		constexpr Display(const Vector2D<T> dimension) : dimension {dimension} { }

	  protected:
		Vector2D<T> dimension;
	};
}
