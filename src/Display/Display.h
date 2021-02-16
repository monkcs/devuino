#pragma once

#include "Vector2D.h"

namespace devuino
{
	template<typename T>
	class Display
	{
	  public:
		constexpr Display(const Vector2D<T> dimension) : dimension(dimension)
		{
		}

		virtual void clear() = 0;

	  protected:
		Vector2D<T> dimension;
	};
}
