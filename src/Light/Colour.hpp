#ifndef Colour_HPP
#define Colour_HPP

#include "../Tools/Iterator.hpp"
#include "Channel.hpp"

#include <stdint.h>

namespace devuino
{
	class Colour
	{
	  public:
		constexpr Colour(const uint8_t red, const uint8_t green, const uint8_t blue) : red {red}, green {green}, blue {blue} {};
		constexpr Colour(const uint32_t hexadecimal) : Colour {static_cast<uint8_t>(hexadecimal >> 16), static_cast<uint8_t>(hexadecimal >> 8), static_cast<uint8_t>(hexadecimal)} {};
		explicit constexpr Colour() : Colour {0, 0, 0} {};

		Channel red;
		Channel green;
		Channel blue;

		constexpr Channel operator[](const uint8_t index) const
		{
			return (index == 0) ? red : ((index == 1) ? green : blue);
		};

		Channel& operator[](const uint8_t index)
		{
			return (index == 0) ? red : ((index == 1) ? green : blue);
		};

		/*	devuino::tools::Iterator<const Channel> begin() const
			{
				return {red};
			}
			devuino::tools::Iterator<const Channel> end() const
			{
				return {red + 3};
			}
			devuino::tools::Iterator<Channel> begin()
			{
				return {red};
			}
			devuino::tools::Iterator<Channel> end()
			{
				return {red + 3};
			}*/
	};
}

#endif
