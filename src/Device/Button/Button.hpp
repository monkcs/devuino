#pragma once

#include "../../Onboard/Digital.hpp"
#include "../../Onboard/Pin.hpp"

namespace devuino::device
{
	using namespace devuino::pin;

	template<typename DigitalBackend = devuino::onboard::DigitalInput>
	class Button
	{
		DigitalBackend pin;
		Resistor pull;
		bool debounce;

	  public:
		Button(const DigitalBackend pin, const Resistor pull = Resistor::None, const bool debounce = false) :
			pin {pin}, pull {pull}, debounce {debounce}
		{
			this->pin.resistor(pull);
		}

		operator bool() const
		{
			if (false /* debounce */)
			{
				// TODO IMPLEMENT DEBOUNCE
				return false;
			}
			else
			{
				const bool reading = pin;
				return (pull == Resistor::PullUp) ? !reading : reading;
			}
		}
	};
}