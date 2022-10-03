#pragma once

namespace devuino
{
	template<typename Type>
	class Vector2D
	{
	  public:
		constexpr Vector2D(const Type x, const Type y) : x {x}, y {y} {};

		Type x;
		Type y;

		constexpr Type area() const { return x * y; }
	};
}
