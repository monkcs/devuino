#pragma once

#include "../../Delay/DelaySync.h"
#include "../../Input/InputAnalog.hpp"
#include "../../Pin/Pin.hpp"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class Potentiometer : public InputAnalog
		{
		  public:
			Potentiometer(const T pin, const bool debounce = false, const uint8_t iterations = 10, const Resolution bitresolution = Resolution {10}) : InputAnalog {bitresolution, debounce}, pin {pin}, iterations {iterations}
			{
				this->pin.initiate(pin::Input::Analog);
			};

			double fraction() const
			{
				return static_cast<double>(value()) / bitsize.maximum;
			};

			int value() const
			{
				if (debounce && iterations > 1)
				{
					long int reading = 0;

					for (uint8_t counter = 0; counter < iterations; counter++)
					{
						reading += pin.analog();
						DelaySync(5);
					}

					return reading / iterations;
				}
				else
				{
					return pin.analog();
				}
			};

		  protected:
			T pin;
			uint8_t iterations;
		};
	}
}