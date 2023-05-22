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

	/// @brief Fade from Origin to Target
	/// @tparam LightSource Needs to provide 'devuino::utilities::Resolution resolution()' and 'void brightness(integer)'
	/// @param light Light to fade
	/// @param origin Origin to fade from
	/// @param target Target to fade to
	template<typename LightSource>
	static constexpr void fade(LightSource& light, const Origin origin, const Target target)
	{
		fade(light, origin, target, []() {});
	};

	/// @brief Fade from Origin to Target
	/// @tparam LightSource Needs to provide 'devuino::utilities::Resolution resolution()' and 'void brightness(integer)'
	/// @param light Light to fade
	/// @param origin Origin to fade from
	/// @param target Target to fade to
	/// @param function Lambda to call after each fade step
	template<typename LightSource, typename Lambda>
	static constexpr void fade(LightSource& light, const Origin origin, const Target target, Lambda function)
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
