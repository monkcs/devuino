#pragma once

#include "../../Delay/DelaySync.h"
#include "../../Pin/Pin.hpp"

namespace devuino
{
	namespace device
	{
		template<typename Type>
		class Potentiometer
		{
		  public:
			Potentiometer(const Type pin,
						  const bool debounce = false,
						  const uint8_t iterations = 10,
						  const Resolution bitresolution = Resolution {10}) :
				pin {pin}, bitsize {bitresolution}, iterations {iterations}, debounce {debounce}
			{
				this->pin.initiate(pin::Input::Analog);
			};

			double fraction() const { return static_cast<double>(value()) / static_cast<double>(bitsize.maximum); };

			unsigned int value() const
			{
				if (debounce)
				{
					unsigned long int total = 0;

					for (uint8_t i = 0; i < iterations; i++)
					{
						total += pin.analog();
						DelaySync(5);
					}

					return total / iterations;
				}
				else
				{
					return pin.analog();
				}
			};

		  protected:
			Type pin;
			Resolution bitsize;
			uint8_t iterations;
			bool debounce;
		};
	}
}