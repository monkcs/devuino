#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

namespace devuino
{
	template<typename T>
	class Vector2D
	{
	  public:
		constexpr Vector2D(const T x, const T y) : x {x}, y {y} {};

		T x;
		T y;

		constexpr T area() const
		{
			return x * y;
		}
	};
}

#endif
