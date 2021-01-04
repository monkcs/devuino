#ifndef HCSR04_HPP
#define HCSR04_HPP

#include "../../Delay/DelaySync.h"
#include "../../Distance/Distance.hpp"
#include "../Switch/Switch.hpp"

namespace devuino
{
	namespace device
	{
		template<class Trigger, class Echo = Trigger>
		class HCSR04 : public DistanceInput
		{
		  public:
			HCSR04(const Trigger trigger, const Echo echo, const Distance minimum = 2_centimetre, const Distance maximum = 4_metre) : trigger {Switch<Trigger> {trigger}}, echo {echo}, minimum {minimum}, maximum {maximum}
			{
				this->echo.initiate(pin::Input::Digital, pin::Resistor::None);
			}

			operator Distance() const
			{
				return distance();
			};

			Distance distance() const
			{
				/*
				   To trigger a distance reading, a 10 microsecond
				   high on the trigger pin needs to happend.

				   To get the distance in metre, divide the reading
				   by 5800.
				*/

				trigger = true;
				DelaySync(10);
				trigger = false;

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

		  protected:
			Switch<Trigger> trigger;
			Echo echo;

			Distance minimum;
			Distance maximum;
		};
	}
}

#endif
