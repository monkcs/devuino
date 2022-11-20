#pragma once

#include "../Utilities/Resolution/Resolution.hpp"

#include <Arduino.h>
#include <stdint.h>

namespace devuino::onboard
{

	using namespace devuino::utilities;
	class AnalogInput
	{
		uint8_t arduinoPin;

	  public:
		Resolution<10> bitsize {};

		AnalogInput(const uint8_t arduinoPin, const uint8_t pin, volatile uint8_t& ddr) : arduinoPin {arduinoPin} { ddr &= ~(1 << pin); }
		operator int() const { return analogRead(arduinoPin); }
		/*
		AnalogInput(const uint8_t pin) : pin {pin}
		{
			volatile uint8_t& direction {*portModeRegister(digitalPinToPort(pin))};
			const uint8_t bitmask {digitalPinToBitMask(pin)};

			direction &= ~bitmask;
		}
		*/
	};

	class AnalogOutput
	{
		uint8_t pin;

	  public:
		Resolution<8> bitsize {};

		explicit AnalogOutput(const uint8_t pin) : pin {pin} { }
		void operator=(const int value) const { analogWrite(pin, value); }
	};
}