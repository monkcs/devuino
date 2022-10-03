#pragma once

#include <stdint.h>

namespace devuino::utilities
{
	class Colour
	{
	  public:
		enum class Channel
		{
			Red = 0,
			Green = 1,
			Blue = 2
		};

		uint8_t red;
		uint8_t green;
		uint8_t blue;

		explicit constexpr Colour() : Colour {0, 0, 0} { }
		constexpr Colour(const uint8_t red, const uint8_t green, const uint8_t blue) : red {red}, green {green}, blue {blue} { }
		constexpr Colour(const uint32_t packed) :
			Colour {static_cast<uint8_t>(packed >> 16), static_cast<uint8_t>(packed >> 8), static_cast<uint8_t>(packed)} {};

		constexpr uint8_t operator[](const uint8_t index) const { return index == 0 ? red : (index == 1 ? green : blue); }
		uint8_t& operator[](const uint8_t index) { return index == 0 ? red : (index == 1 ? green : blue); }
	};
}
