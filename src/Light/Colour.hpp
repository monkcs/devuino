#pragma once

#include <stdint.h>

namespace devuino
{
	class Colour
	{
	  public:
		constexpr Colour(const uint8_t red, const uint8_t green, const uint8_t blue) : red {red}, green {green}, blue {blue} {};
		constexpr Colour(const uint32_t hexadecimal) :
			Colour {static_cast<uint8_t>(hexadecimal >> 16), static_cast<uint8_t>(hexadecimal >> 8), static_cast<uint8_t>(hexadecimal)} {};
		explicit constexpr Colour() : Colour {0, 0, 0} {};

		constexpr uint8_t operator[](const uint8_t index) const { return (index == 0) ? red : ((index == 1) ? green : blue); };
		uint8_t& operator[](const uint8_t index) { return (index == 0) ? red : ((index == 1) ? green : blue); };

		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};
}
