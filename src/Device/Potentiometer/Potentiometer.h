#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../../Delay/DelaySync.h"
#include "../../Input/InputAnalog.h"
#include "../../Pin/Pin.h"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class Potentiometer : public InputAnalog
		{
		  public:
			Potentiometer(const T pin, const bool debounce = false, const uint8_t iterations = 10, const Resolution bitresolution = Resolution(10)) : InputAnalog(bitresolution, debounce), pin(pin), iterations(debounce ? iterations : 1)
			{
				this->pin.initiate(pin::Input::Analog);
			};

			int value() const override
			{
				unsigned int reading = 0;
				for (auto counter = 0; counter < iterations; counter++)
				{
					reading += pin.analogread();
					DelaySync(5);
				}
				return (reading / iterations);
			};

		  private:
			T pin;
			uint8_t iterations;
		};
	}
}

#endif
