#pragma once

#include "../../Onboard/Digital.hpp"
#include "../../Onboard/Pin.hpp"

namespace devuino::device
{
	using namespace devuino::pin;

	/// @brief Button is a generic digital input
	/// @tparam DigitalBackend Physical or logical pin
	template<typename DigitalBackend = devuino::onboard::DigitalInput>
	class Button
	{
		DigitalBackend pin;
		Resistor pull;
		bool debounce;

	  public:
		/// @brief Button is a generic digital input
		/// @param pin Physical or logical pin
		/// @param pull Configure internal pull resistors
		/// @param debounce Configure debounce mitigation
		constexpr Button(const DigitalBackend pin, const Resistor pull = Resistor::None, const bool debounce = false) :
			pin {pin}, pull {pull}, debounce {debounce}
		{
			this->pin.resistor(pull);
		}

		/// @brief Value of button
		constexpr operator bool() const
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