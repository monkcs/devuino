#pragma once

#include "Vector2D.hpp"

namespace devuino
{
	template<typename Type>
	class Vector3D : public Vector2D
	{
	  public:
		constexpr Vector3D(const Type x, const Type y, const Type z) : Vector2D {x, y}, z {z} {};

		Type z;

		constexpr Type area() = delete;
		constexpr Type volume() const { return x * y * z; }
	};
}
