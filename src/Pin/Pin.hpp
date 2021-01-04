#ifndef PIN_HPP
#define PIN_HPP

#include <stdint.h>

namespace devuino
{
	namespace pin
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
}

#endif
