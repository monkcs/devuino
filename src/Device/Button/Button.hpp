#pragma once

#include "../../Pin/Pin.hpp"

namespace devuino::device
{
	using namespace devuino::pin;

	template<typename T>
	class Button
	{
	  public:
		Button(const T pin, const Resistor pull, const bool debounce = false) : pin {pin}, pull {pull}, debounce {debounce}
		{
			this->pin.initiate(Input::Digital, pull);
		};

		operator bool() const { return value(); };

		bool value() const
		{
			if (false /* debounce */)
			{
				// TODO IMPLEMENT DEBOUNCE
				return false;
			}
			else
			{
				const bool reading = pin.digital();
				return (pull == Resistor::PullUp) ? !reading : reading;
			}
		};

	  protected:
		T pin;
		Resistor pull;
		bool debounce;
	};

}