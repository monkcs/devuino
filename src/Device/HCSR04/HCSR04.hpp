#pragma once

#include "../../Utilities/Lenght/Lenght.hpp"
#include "../Switch/Switch.hpp"

#include <stdint.h>

namespace devuino::device
{
	using namespace devuino::utilities;
	using devuino::utilities::Lenght;

	template<typename Trigger = devuino::onboard::DigitalOutput, typename Echo = devuino::onboard::DigitalInput>
	class HCSR04
	{
		Switch<Trigger> trigger;
		Echo echo;

		Lenght minimum;
		Lenght maximum;

		bool debounce;

	  public:
		HCSR04(const Trigger trigger,
			   const Echo echo,
			   const bool debounce = false,
			   const Lenght minimum = 2_centimetre,
			   const Lenght maximum = 4_metre) :
			trigger {Switch<Trigger> {trigger}}, echo {echo}, minimum {minimum}, maximum {maximum}, debounce {debounce}
		{
			this->echo.resistor(devuino::pin::Resistor::None);
		}

		operator Lenght() const { return distance(); };

		Lenght distance() const
		{
			if (debounce)
			{
				const unsigned int iterations {10};

				Lenght total {};

				for (uint8_t i = 0; i < iterations; i++)
				{
					total += measurement();
				}

				return total / iterations;
			}
			else
			{
				return measurement();
			}
		};

	  private:
		Lenght measurement() const
		{
			/*
				To trigger a distance measurement, a 10 microsecond
				high on the trigger pin needs to happend.

				To get the distance in metre, divide the measurement
				by 5800.
			*/

			trigger.on();
			delay(10);
			trigger.off();

			const auto reading = Lenght {pulseIn(echo.pin(), true, 70) / 5800.0};

			if (reading > maximum)
			{
				return maximum;
			}
			else if (reading < minimum)
			{
				return minimum;
			}
			else
			{
				return reading;
			}
		}
	};
}
