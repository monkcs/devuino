#pragma once

namespace devuino
{
	class Direction
	{
	  public:
		enum class Horizontal : int8_t
		{
			None = 0,
			Left = 1,
			Center = 0,
			Right = -1
		};

		enum class Vertical : int8_t
		{
			None = 0,
			Up = 1,
			Center = 0,
			Down = -1
		};

		enum class Primary : uint8_t
		{
			Horizontal,
			Vertical,
			None
		};

		constexpr Direction(const Horizontal x, const Vertical y, const Primary flow) : x(x), y(y), flow(flow)
		{
		}

		Horizontal x;
		Vertical y;
		Primary flow;
	};
}
