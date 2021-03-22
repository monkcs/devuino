#pragma once

#include "../../Output/OutputDigital.hpp"
#include "../../Pin/Pin.hpp"

namespace devuino::device
{
	template<typename T>
	class Switch : public OutputDigital
	{
	  public:
		Switch(const T pin, const bool initial = false) : OutputDigital {initial}, pin {pin}
		{
			this->pin.initiate(devuino::pin::Output::Digital);
			set(initial);
		};

		~Switch() { set(false); };

		constexpr operator bool() const { return status; };

		void operator=(const bool value) const { set(value); };
		void operator=(const bool value) { set(value); };

	  protected:
		T pin;

		void set(const bool value) const override { pin.digital(value); };
		void set(const bool value) override
		{
			status = value;
			pin.digital(value);
		};
	};
}