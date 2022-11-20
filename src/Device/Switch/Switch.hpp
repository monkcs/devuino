#pragma once

#include "../../Onboard/Digital.hpp"

namespace devuino::device
{
	template<typename DigitalBackend = devuino::onboard::DigitalOutput>
	class Switch
	{
		DigitalBackend pin;

	  public:
		constexpr Switch(const DigitalBackend pin, const bool initial = false) : pin {pin} { this->pin = initial; }

		~Switch() { off(); }

		constexpr operator bool() const { return pin; }

		constexpr Switch& operator=(const bool value)
		{
			pin = value;
			return *this;
		}

		constexpr void off() { pin = false; }
		constexpr void on() { pin = true; }

		constexpr void toggle() { pin.toggle(); }
	};
}