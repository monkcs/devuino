#pragma once

#include "../../Input/InputDigital.hpp"
#include "../../Pin/Pin.hpp"

namespace devuino::device
{
	using namespace devuino::pin;

	template<typename T>
	class Button : public InputDigital
	{
	  public:
		Button(const T pin, const Resistor pull, const bool debounce = false) : InputDigital {debounce}, pin {pin}, pull {pull} { this->pin.initiate(Input::Digital, pull); };

		/* Return true if button is pressed */
		operator bool() const { return value(); };

		/* Return true if button is pressed */
		bool value() const override
		{
			if (false /* debounce */)
			{
				// TODO IMPLEMENT DEBOUNCE
				return false;
			}
			else
			{
				return (pull == Resistor::PullUp) ? !pin.digital() : pin.digital();
			}
		};

	  protected:
		T pin;
		Resistor pull;
	};

}