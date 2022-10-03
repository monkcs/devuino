#pragma once

#include "../../Onboard/Analog.hpp"
#include "../../Utilities/Resolution/Resolution.hpp"

namespace devuino
{
	namespace device
	{
		template<typename AnalogBackend = devuino::onboard::AnalogInput>
		class Potentiometer
		{
			AnalogBackend pin;
			devuino::utilities::Resolution bitsize;
			uint8_t iterations;
			bool debounce;

		  public:
			Potentiometer(const AnalogBackend pin,
						  const bool debounce = false,
						  const uint8_t iterations = 10,
						  const devuino::utilities::Resolution bitresolution = Resolution {10}) :
				pin {pin}, bitsize {bitresolution}, iterations {iterations == 0 ? 1 : iterations}, debounce {debounce} {};

			double fraction() const { return static_cast<double>(this->operator int()) / static_cast<double>(bitsize.maximum); }

			operator int() const
			{
				if (debounce)
				{
					long int total = 0;

					for (uint8_t i = 0; i < iterations; i++)
					{
						total += pin;
						delay(5);
					}

					return total / iterations;
				}
				else
				{
					return pin;
				}
			}
		};
	}
}