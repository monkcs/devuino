#pragma once

#include "Colour.hpp"

namespace devuino
{
	class Spectrum
	{
	  public:
		constexpr Spectrum(const Colour::Channel start) :
			colour {(start == Colour::Channel::Red) ? 255 : 0, (start == Colour::Channel::Green) ? 255 : 0,
					(start == Colour::Channel::Blue) ? 255 : 0} {};

		constexpr operator Colour() const { return {colour}; };

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
