#pragma once

#include <stdint.h>

namespace devuino::utilities
{
	class Direction
	{
	  public:
		enum class Horizontal : int8_t
		{
			None,
			Left,
			Center,
			Right
		};

		enum class Vertical : int8_t
		{
			None,
			Up,
			Center,
			Down
		};

		enum class Primary : uint8_t
		{
			Horizontal,
			Vertical,
			None
		};

		constexpr Direction(const Horizontal x, const Vertical y, const Primary flow) : x {x}, y {y}, flow {flow} {};

		Horizontal x;
		Vertical y;
		Primary flow;
	};
}
