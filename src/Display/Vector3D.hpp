#pragma once

#include "Vector2D.hpp"

namespace devuino
{
	template<typename T>
	class Vector3D : public Vector2D
	{
	  public:
		constexpr Vector3D(const T x, const T y, const T z) : Vector2D {x, y}, z {z} {};

		T z;

		constexpr T area() = delete;
		constexpr T volume() const { return x * y * z; }
	};
}
