#pragma once

#include "../../Pin/Pin.hpp"

namespace devuino::device
{
	template<typename Type>
	class Switch
	{
	  public:
		Switch(const Type pin, const bool initial = false) : pin {pin}, status {initial}
		{
			this->pin.initiate(devuino::pin::Output::Digital);
			set(initial);
		};

		~Switch() { set(false); };

		operator bool() { return status; };

		void operator=(const bool value) const { set(value); };
		void operator=(const bool value) { set(value); };

		void off() const { set(false); };
		void off() { set(false); };

		void on() const { set(true); };
		void on() { set(true); };

		void toggle() { set(!status); };

	  protected:
		Type pin;
		bool status;

		void set(const bool value) const { pin.digital(value); };
		void set(const bool value)
		{
			status = value;
			pin.digital(value);
		};
	};
}