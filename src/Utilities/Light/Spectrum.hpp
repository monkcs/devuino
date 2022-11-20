#pragma once

#include "Colour.hpp"

namespace devuino::utilities
{
	class Spectrum
	{
		Colour colour;

	  public:
		constexpr Spectrum(const Colour start) : colour {start} { }

		constexpr operator Colour() const { return colour; }

		[[nodiscard]] constexpr Colour next()
		{
			if (colour.red > 0)
			{
				colour.green += 1;
			}
			if (colour.blue > 0)
			{
				colour.green -= 1;
			}

			if (colour.green > 0)
			{
				colour.blue += 1;
			}
			if (colour.red > 0)
			{
				colour.blue -= 1;
			}

			if (colour.blue > 0)
			{
				colour.red += 1;
			}
			if (colour.green > 0)
			{
				colour.red -= 1;
			}

			return colour;
		}
	};
}
