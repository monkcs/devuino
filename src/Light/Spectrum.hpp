#pragma once

#include "Colour.hpp"

namespace devuino
{
	class Spectrum
	{
	  public:
		constexpr Spectrum(const Colour start) : colour {start} {};

		constexpr operator Colour() const { return current(); };

		constexpr Colour current() const { return colour; };

		[[nodiscard]] Colour next()
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
		};

	  private:
		Colour colour;
	};
}
