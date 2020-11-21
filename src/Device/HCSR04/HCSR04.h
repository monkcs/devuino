#ifndef HCSR04_H
#define HCSR04_H

#include "../../Delay/DelaySync.h"
#include "../../Distance/Distance.h"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class HCSR04 : public DistanceInput
		{
		  public:
			HCSR04(const T trigger, const T echo, const Distance minimum = 2_centimetre, const Distance maximum = 4_metre) : trigger(trigger), echo(echo), minimum(minimum), maximum(maximum)
			{
				this->trigger.initiate(pin::Output::Digital);
				this->echo.initiate(pin::Input::Digital, pin::Resistor::None);
			}

			Distance distance() const override
			{
				/*
				   To trigger a distance reading, a 10 microsecond
				   high on the trigger pin needs to happend.

				   To get the distance in metre, divide the reading
				   by 5800.
				*/
				trigger.digitalwrite(false);
				DelaySync(5);
				trigger.digitalwrite(true);
				DelaySync(10);
				trigger.digitalwrite(false);

				const Distance reading = Distance {pulseIn(echo.pin, true, 70) / 5800.0};

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

		  private:
			Distance minimum;
			Distance maximum;
			T trigger;
			T echo;
		};
	}
}

#endif
