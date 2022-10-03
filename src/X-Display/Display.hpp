#pragma once

#include "Vector2D.hpp"

namespace devuino
{
	template<typename Type>
	class Display
	{
	  public:
		constexpr Display(const Vector2D<Type> dimension) : dimension {dimension} { }

	  protected:
		Vector2D<Type> dimension;
	};
}
