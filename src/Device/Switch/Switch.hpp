#pragma once

#include "../../Onboard/Digital.hpp"

namespace devuino::device
{
	template<typename DigitalBackend = devuino::onboard::DigitalOutput>
	class Switch
	{
		DigitalBackend pin;

	  public:
		Switch(const DigitalBackend pin, const bool initial = false) : pin {pin} { operator=(initial); }

		~Switch() { off(); }

		operator bool() const { return pin; }

		void operator=(const bool value) { pin = value; }

		void off() { operator=(false); }
		void on() { operator=(true); }

		void toggle() { pin.toggle(); }
	};
}