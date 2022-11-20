#pragma once

#include "../../Device/Light/Light.hpp"
#include "../Resolution/Resolution.hpp"

#include <stdint.h>

namespace devuino::utilities::animation
{

	enum class Target
	{
		Minimum,
		Maximum
	};

	enum class Origin
	{
		Current,
		Minimum,
		Maximum
	};

	/* A LightSource needs to provide 'this->operator devuino::utilities::Resolution()'
	   and this->brightness(integer) */
	template<typename LightSource>
	static void fade(LightSource& light, const Origin origin, const Target target)
	{
		fade(light, origin, target, []() {});
	};

	/* A LightSource needs to provide 'this->operator devuino::utilities::Resolution()'
	   and this->brightness(integer) */
	template<typename LightSource, typename Lambda>
	static void fade(LightSource& light, const Origin origin, const Target target, Lambda function)
	{
		if (origin == Origin::Current)
		{
			if (target == Target::Minimum)
			{
				for (auto value = light.brightness(); value--;)
				{
					light.brightness(value);
					function();
				}
			}
			else if (target == Target::Maximum)
			{
				for (auto value = light.brightness(); value < light.resolution().maximum; ++value)
				{
					light.brightness(value);
					function();
				}
			}
		}
		else if (origin == Origin::Minimum)
		{
			if (target == Target::Minimum)
			{
				light.brightness(0);
				function();
			}
			else if (target == Target::Maximum)
			{
				for (decltype(light.resolution().maximum) value = 0; value < light.resolution().maximum; ++value)
				{
					light.brightness(value);
					function();
				}
			}
		}
		else if (origin == Origin::Maximum)
		{
			if (target == Target::Minimum)
			{
				for (auto value = light.resolution().maximum; value--;)
				{
					light.brightness(value);
					function();
				}
			}
			else if (target == Target::Maximum)
			{
				light.brightness(light.resolution().maximum);
				function();
			}
		}
	}
};
