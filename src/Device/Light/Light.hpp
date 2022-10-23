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
		Resolution bitsize;
		unsigned int bright;
		bool status;

	  public:
		Light(const AnalogBackend pin, const bool initial = false, const Resolution bitresolution = Resolution {8}) :
			pin {pin}, bitsize {bitresolution}, bright {bitresolution.maximum}, status {initial}
		{
			set(initial);
		}

		Light(const AnalogBackend pin,
			  const unsigned int brightness,
			  const bool initial = false,
			  const Resolution bitresolution = Resolution {8}) :
			pin {pin}, bitsize {bitresolution}, bright {brightness}, status {initial}
		{
			set(initial);
		}

		~Light() { set(false); }

		Light& operator=(const bool value)
		{
			set(value);
			return *this;
		}

		Light& operator+=(const unsigned int value)
		{
			bright += value;
			set();
			return *this;
		}

		Light& operator-=(const unsigned int value)
		{
			bright -= value;
			set();
			return *this;
		}

		Light& operator*=(const unsigned int change)
		{
			bright *= change;
			set();
			return *this;
		}

		Light& operator/=(const unsigned int change)
		{
			bright /= change;
			set();
			return *this;
		}

		void brightness(const unsigned int value)
		{
			bright = value;
			set();
		}
		constexpr unsigned int brightness() const { return bright; }
		void fraction(const double value) { brightness(static_cast<unsigned int>(bitsize.maximum * value)); }

		void off() { set(false); }
		void on() { set(true); }
		void toggle() { set(!status); }

		void set() { pin = bright; }
		void set(const bool value)
		{
			status = value;
			pin = (value ? bright : 0);
		}
	};
}