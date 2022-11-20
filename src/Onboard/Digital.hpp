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

	  public:
		DigitalInput(const uint8_t pin, volatile uint8_t& port, volatile uint8_t& input, volatile uint8_t& ddr) :
			bitmask {static_cast<uint8_t>(1 << pin)}, internal_resistor {port}, input {input}
		{
			ddr |= bitmask;
		}

		/*
			DigitalInput(const uint8_t pin) :
			bitmask {digitalPinToBitMask(pin)},
			internal_resistor {*portOutputRegister(digitalPinToPort(pin))},
			input {*portInputRegister(digitalPinToPort(pin))},
			pin_number {pin}
			{
				volatile uint8_t& direction {*portModeRegister(digitalPinToPort(pin))};
				direction &= ~bitmask;
			}
		*/

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
	};

	class DigitalOutput
	{
		uint8_t bitmask;
		volatile uint8_t& port;

	  public:
		DigitalOutput(const uint8_t pin, volatile uint8_t& port, volatile uint8_t& ddr) :
			bitmask {static_cast<uint8_t>(1 << pin)}, port {port}
		{
			ddr |= bitmask;
		}

		/*
			DigitalOutput(const uint8_t pin) : bitmask {digitalPinToBitMask(pin)}, output {*portOutputRegister(digitalPinToPort(pin))}
			{
				volatile uint8_t& direction {*portModeRegister(digitalPinToPort(pin))};
				direction |= bitmask;
			}
		*/
		operator bool() const { return port & bitmask; }

		DigitalOutput& operator=(const bool value)
		{
			if (value)
			{
				port |= bitmask;
			}
			else
			{
				port &= ~bitmask;
			}

			return *this;
		}

		void toggle() { port ^= bitmask; }
	};
}