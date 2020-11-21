#ifndef PIN_H
#define PIN_H

#include <stdint.h>

namespace devuino
{
	namespace pin
	{
		enum class Input : uint8_t
		{
			Analog,
			Digital
		};

		enum class Output : uint8_t
		{
			Analog,
			Digital
		};

		enum class Resistor : uint8_t
		{
			PullUp,
			PullDown,
			None
		};

		class Pin
		{
		  public:
			constexpr Pin(const uint8_t pin) : pin {pin} {};

			uint8_t pin;
			/*virtual int analogread() const = 0;
			 virtual void analogwrite(const int value) const = 0;
			 virtual bool digitalread() const = 0;
			 virtual void digitalwrite(const bool value) const = 0;

			 virtual void initiate(const pin::Input mode, const Resistor pull) const = 0;
			 virtual void initiate(const pin::Output mode) const = 0;*/
		};
	}
}

#endif
