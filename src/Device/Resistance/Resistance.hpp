#pragma once

#include "../../Utilities/Resolution/Resolution.hpp"
#include "../Potentiometer/Potentiometer.hpp"
#include "../Switch/Switch.hpp"

namespace devuino::device
{
	template<typename Signal = devuino::onboard::DigitalInput, typename Power = devuino::onboard::DigitalOutput>
	class Resistance
	{
		Potentiometer<Signal> signal;
		Switch<Power> power;

	  public:
		/// Make a reading of a analog input from (T signal) by powering on a resistor from the (T power) pin.
		/// That to prevent for example powerdraw and corrosion on water sensors.
		Resistance(const Potentiometer<Signal> signal, const Switch<Power> power) : signal {signal}, power {power} {};

		operator int() const
		{
			power.on();
			const int reading = signal;
			power.off();

			return reading;
		}

		double fraction() const
		{
			power.on();
			const auto reading = signal.fraction();
			power.off();

			return reading;
		}
	};
}
