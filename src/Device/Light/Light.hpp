#pragma once

#include "../../Pin/Pin.hpp"
#include "../../Resolution/Resolution.hpp"

namespace devuino::device
{
	template<class T>
	class Light
	{
	  public:
		Light(const T pin, const unsigned int brightness, const bool initial = false, const Resolution bitresolution = Resolution {8}) :
			pin {pin}, bitsize {bitresolution}, bright {brightness}, status {initial}
		{
			this->pin.initiate(devuino::pin::Output::Analog);
			set(initial);
		};
		Light(const T pin, const bool initial = false, const Resolution bitresolution = Resolution {8}) :
			pin {pin}, bitsize {bitresolution}, bright {bitresolution.maximum}, status {initial}
		{
			this->pin.initiate(devuino::pin::Output::Analog);
			set(initial);
		};

		~Light() { set(false); };

		operator unsigned int() const { return bright; };

		void operator=(const Light<T>& rhs)
		{
			bright = rhs.bright;
			status = rhs.status;
			set();
		};

		void operator=(const unsigned int value) { brightness(value); };

		void operator+=(const unsigned int value)
		{
			bright += value;
			set();
		};
		void operator-=(const unsigned int value)
		{
			bright -= value;
			set();
		};

		void operator*=(const unsigned int change)
		{
			bright *= change;
			set();
		};

		void operator/=(const unsigned int change)
		{
			bright /= change;
			set();
		};

		void brightness(const unsigned int value)
		{
			bright = value;
			set();
		};

		void fraction(const double value) { brightness(static_cast<unsigned int>(bitsize.maximum * value)); };

		void off() const { set(false); };
		void off() { set(false); };

		void on() const { set(true); };
		void on() { set(true); };

		void toggle() { set(!status); };

		void set(const bool value) const { pin.analog(value ? bright : 0); }
		void set(const bool value)
		{
			status = value;
			pin.analog(value ? bright : 0);
		}

	  protected:
		T pin;
		Resolution bitsize;
		unsigned int bright;
		bool status;

		void set() const { set(status); }
	};
}