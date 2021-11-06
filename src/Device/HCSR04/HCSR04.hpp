#pragma once

#include "../../Delay/DelaySync.h"
#include "../../Distance/Distance.hpp"
#include "../Switch/Switch.hpp"

#include <stdint.h>

namespace devuino
{
	namespace device
	{
		template<class Trigger, class Echo = Trigger>
		class HCSR04
		{
		  public:
			HCSR04(const Trigger trigger,
				   const Echo echo,
				   const bool debounce = false,
				   const Distance minimum = 2_centimetre,
				   const Distance maximum = 4_metre) :
				trigger {Switch<Trigger> {trigger}}, echo {echo}, debounce {debounce}, minimum {minimum}, maximum {maximum}
			{
				this->echo.initiate(pin::Input::Digital, pin::Resistor::None);
			}

			operator Distance() const { return distance(); };

			Distance distance() const
			{
				if (debounce)
				{
					const unsigned int iterations {10};

					Distance total {0};

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

		  protected:
			Switch<Trigger> trigger;
			Echo echo;

			bool debounce;

			Distance minimum;
			Distance maximum;

			Distance measurement() const
			{
				/*
					To trigger a distance measurement, a 10 microsecond
					high on the trigger pin needs to happend.

					To get the distance in metre, divide the measurement
					by 5800.
				*/

				trigger.on();
				DelaySync(10);
				trigger.off();

				const auto reading = Distance {pulseIn(echo.get(), true, 70) / 5800.0};

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
}
