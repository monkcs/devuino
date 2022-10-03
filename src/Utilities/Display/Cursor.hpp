#pragma once

#include "../Math/Vector2D.hpp"

namespace devuino::utilities
{
	template<typename Pointer, typename Position>
	class Cursor : public Vector2D<Position>
	{
	  public:
		constexpr Cursor(const Pointer pointer, const Vector2D<Position> position, const bool active) :
			Vector2D<Position> {position}, pointer {pointer}, active {active} {};

		Pointer pointer;
		bool active;
	};
}
