#pragma once

#include "Pin.hpp"

#include <Arduino.h>
#include <stdint.h>

namespace devuino::pin
{
	class Onboard
	{
	  public:
		explicit Onboard(const uint8_t pin) :
			pin {pin},
			bitmask(digitalPinToBitMask(pin)),
			direction(*portModeRegister(digitalPinToPort(pin))),
			port(*portOutputRegister(digitalPinToPort(pin))),
			input(*portInputRegister(digitalPinToPort(pin))) {};

		int analog() const { return analogRead(pin); };

		void analog(const int value) const { analogWrite(pin, value); };

		bool digital() const { return input & bitmask; };

		void digital(const bool value) const
		{
			if (value)
			{
				port |= bitmask;
			}
			else
			{
				port &= ~bitmask;
			}
		};

		void digitaltoggle() const { port ^= bitmask; };

		void initiate([[maybe_unused]] const Input mode, const Resistor pull = Resistor::None) const
		{
			direction &= ~bitmask;

			if (pull == Resistor::PullUp)
			{
				port |= bitmask;
			}
		};

		void initiate(const Output mode) const
		{
			/* There is an extra pinMode call in wiring_analog.c for compability
			   reasons. That means it is not necessary to call pinMode when the
			   pin is configured as an analog output. */

			if (mode == Output::Digital)
			{
				direction |= bitmask;
				port &= ~bitmask;
			}
		};

		constexpr uint8_t get() const { return pin; }

	  protected:
		uint8_t pin;
		uint8_t bitmask;

		volatile uint8_t& direction;
		volatile uint8_t& port;
		volatile uint8_t& input;
	};
}