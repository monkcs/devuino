#pragma once

#include "Colour.hpp"
#include "Light.hpp"

#include <stdint.h>

namespace devuino
{
	class Rgb : public Light
	{
	  public:
		constexpr Rgb(const Colour colours) : Light {Resolution {8}}, colours {colours} {};

		Colour colours;
	};
}
