#pragma once

#include "../Potentiometer/Potentiometer.hpp"
#include "../Switch/Switch.hpp"

namespace devuino
{
	namespace device
	{
		template<class Signal, class Power = Signal>
		class Resistance
		{
		  public:
			/* Make a reading of a analog input from (T signal) by powering on a resistor from the (T power) pin.
			 * That to prevent for example powerdraw and corrosion on water sensors. */

			Resistance(const Signal signal, const Power power, const bool debounce = false, const uint8_t iterations = 10, const Resolution bitresolution = Resolution {10}) : signal {Potentiometer<Signal> {signal, debounce, iterations, bitresolution}}, power {Switch<Power> {power}} {};

			int value() const
			{
				power.on();
				const auto reading = signal.value();
				power.off();

				return reading;
			};

			double fraction() const
			{
				power.on();
				const auto reading = signal.fraction();
				power.off();

				return reading;
			};

		  private:
			Potentiometer<Signal> signal;
			Switch<Power> power;
		};
	}
}
