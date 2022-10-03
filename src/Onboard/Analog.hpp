#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace devuino::onboard
{
	class AnalogInput
	{
		uint8_t pin;

	  public:
		AnalogInput(const uint8_t pin) : pin {pin}
		{
			volatile uint8_t& direction {*portModeRegister(digitalPinToPort(pin))};
			const uint8_t bitmask {digitalPinToBitMask(pin)};

			direction &= ~bitmask;
		}

		operator int() const { return analogRead(pin); }
	};

	class AnalogOutput
	{
		uint8_t pin;

	  public:
		AnalogOutput(const uint8_t pin) : pin {pin} { }

		void operator=(const int value) { analogWrite(pin, value); }
	};
}