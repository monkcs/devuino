#pragma once

#include <stdint.h>

namespace devuino::pin
{
	enum class Input : uint8_t
	{
		Analog,
		Digital
	};

	enum class Output : uint8_t
	{
		Analog,
		Digital
	};

	enum class Resistor : uint8_t
	{
		PullUp,
		PullDown,
		None
	};
}
