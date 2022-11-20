#pragma once

#include "../../Onboard/Analog.hpp"
#include "../../Utilities/Resolution/Resolution.hpp"

namespace devuino::device
{
	using devuino::utilities::Resolution;

	template<typename AnalogBackend = devuino::onboard::AnalogOutput>
	class Light
	{
		AnalogBackend pin;
		decltype(pin.bitsize.maximum) bright;
		bool status;

	  public:
		Light(const AnalogBackend pin, const bool initial = false) : Light {pin, pin.bitsize.maximum, initial} { }
		Light(const AnalogBackend pin, const bool initial, const decltype(pin.bitsize.maximum) brightness) :
			pin {pin}, bright {brightness}, status {initial}
		{
			set(initial);
		}

		~Light() { off(); }

		void off() const { pin = 0; }
		void on() const { pin = bright; }
		const Light& operator=(const bool value) const
		{
			value ? on() : off();
			return *this;
		}

		constexpr operator bool() { return bright == 0 ? false : status; }
		Light& operator=(const bool value)
		{
			set(value);
			return *this;
		}

		Light& operator+=(const decltype(pin.bitsize.maximum) value)
		{
			bright += value;
			set();
			return *this;
		}

		Light& operator-=(const decltype(pin.bitsize.maximum) value)
		{
			bright -= value;
			set();
			return *this;
		}

		void brightness(const decltype(pin.bitsize.maximum) value)
		{
			bright = value;
			set();
		}
		constexpr decltype(pin.bitsize.maximum) brightness() const { return bright; }
		void fraction(const double value) { brightness(static_cast<decltype(pin.bitsize.maximum)>(pin.bitsize.maximum * value)); }

		void off() { set(false); }
		void on() { set(true); }
		void toggle() { set(!status); }

		void set() { pin = (status ? bright : 0); }
		void set(const bool value)
		{
			status = value;
			pin = (value ? bright : 0);
		}

		constexpr decltype(pin.bitsize) resolution() const { return pin.bitsize; }
	};
}