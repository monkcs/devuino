#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "../Potentiometer/Potentiometer.h"
#include "../Switch/Switch.h"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class Resistance
		{
		  public:
			/* Make a reading of a analog input from (T signal) by powering on a resistor from the (T power) pin.
			 * That to prevent for example powerdraw and corrosion on water sensors. */

			Resistance(const T signal, const T power, const bool debounce = false, const unsigned int iterations = 10, const Resolution bitresolution = Resolution(10)) : signal(Potentiometer<T>(signal, debounce, iterations, bitresolution)), power(Switch<T>(power))
			{
			}

			[[nodiscard]] int value() const
			{
				power.on();
				const auto reading = signal.value();
				power.off();

				return reading;
			}

			[[nodiscard]] double percent() const
			{
				power.on();
				const auto reading = signal.percent();
				power.off();

				return reading;
			}

		  private:
			Potentiometer<T> signal;
			Switch<T> power;
		};
	}
}

#endif
