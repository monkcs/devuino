#pragma once

#include "../../Input/InputDigital.h"
#include "../../Pin/Pin.hpp"

namespace devuino
{
	namespace device
	{
		using namespace devuino::pin;

		template<typename T>
		class Button : public InputDigital
		{
		  public:
			Button(const T pin, const Resistor pull) : InputDigital {false}, pin {pin}, pull {pull}
			{
				this->pin.initiate(Input::Digital, pull);
			};

			operator bool() const
			{
				return value();
			};

			bool value() const
			{
				return (pull == Resistor::PullUp) ? !pin.digital() : pin.digital();
			};

		  protected:
			T pin;
			Resistor pull;
		};
	}
}