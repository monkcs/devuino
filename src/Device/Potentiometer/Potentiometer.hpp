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
			uint8_t iterations;
			bool debounce;

		  public:
			constexpr Potentiometer(const AnalogBackend pin, const bool debounce = false, const uint8_t iterations = 10) :
				pin {pin}, iterations {iterations}, debounce {iterations < 2 ? false : debounce} {};

			constexpr double fraction() const
			{
				return static_cast<double>(this->operator int()) / static_cast<double>(pin.bitsize.maximum);
			}

			constexpr operator int() const
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

			constexpr decltype(pin.bitsize) resolution() const { return pin.bitsize; }
		};
	}
}