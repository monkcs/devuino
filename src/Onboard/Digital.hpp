#pragma once

#include "Pin.hpp"

#include <Arduino.h>
#include <stdint.h>

namespace devuino::onboard
{
	class DigitalInput
	{
		uint8_t bitmask;
		volatile uint8_t& internal_resistor;
		volatile uint8_t& input;
		uint8_t pin_number;

	  public:
		DigitalInput(const uint8_t pin) :
			bitmask {digitalPinToBitMask(pin)},
			internal_resistor {*portOutputRegister(digitalPinToPort(pin))},
			input {*portInputRegister(digitalPinToPort(pin))},
			pin_number {pin}
		{
			volatile uint8_t& direction {*portModeRegister(digitalPinToPort(pin))};
			direction &= ~bitmask;
		}

		operator bool() const { return input & bitmask; }

		void resistor(const devuino::pin::Resistor pull)
		{
			if (pull == devuino::pin::Resistor::PullUp)
			{
				internal_resistor |= bitmask;
			}
			else
			{
				internal_resistor &= ~bitmask;
			}
		}

		uint8_t pin() const { return pin_number; }
	};

	class DigitalOutput
	{
		uint8_t bitmask;
		volatile uint8_t& output;

	  public:
		DigitalOutput(const uint8_t pin) : bitmask {digitalPinToBitMask(pin)}, output {*portOutputRegister(digitalPinToPort(pin))}
		{
			volatile uint8_t& direction {*portModeRegister(digitalPinToPort(pin))};
			direction |= bitmask;
		}

		operator bool() const { return output & bitmask; }

		void operator=(const bool value)
		{
			if (value)
			{
				output |= bitmask;
			}
			else
			{
				output &= ~bitmask;
			}
		}

		void toggle() { output ^= bitmask; }
	};
}