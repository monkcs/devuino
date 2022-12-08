#pragma once

#include "../../Onboard/Analog.hpp"
#include "../../Utilities/Resolution/Resolution.hpp"

namespace devuino::device
{
	using devuino::utilities::Resolution;

	/// @brief Light is a generic analog output for controlling light sources
	/// @tparam AnalogBackend Physical or logical pin
	template<typename AnalogBackend = devuino::onboard::AnalogOutput>
	class Light
	{
		AnalogBackend pin;
		decltype(pin.bitsize.maximum) bright;
		bool status;

	  public:
		/// @brief Light is a generic analog output for controlling light sources
		/// @param pin Physical or logical pin
		/// @param initial Configure light on or off
		Light(const AnalogBackend pin, const bool initial = false) : Light {pin, initial, pin.bitsize.maximum} { }

		/// @brief Light is a generic analog output for controlling light sources
		/// @param pin Physical or logical pin
		/// @param initial Configure light on or off
		/// @param brightness Configure light brightness
		Light(const AnalogBackend pin, const bool initial, const decltype(pin.bitsize.maximum) brightness) :
			pin {pin}, bright {brightness}, status {initial}
		{
			set(initial);
		}

		~Light() { off(); }

		const Light& operator=(const bool value) const
		{
			value ? on() : off();
			return *this;
		}
		Light& operator=(const bool value)
		{
			set(value);
			return *this;
		}

		/// @brief Get status of light
		/// @returns False if brightness is zero or the light is off
		constexpr operator bool() { return bright == 0 ? false : status; }

		/// @brief Increment brightness
		Light& operator+=(const decltype(pin.bitsize.maximum) value)
		{
			bright += value;
			set();
			return *this;
		}
		/// @brief Decrement brightness
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

		/// @brief Set brightness
		/// @param value New brightness in range [0..1]
		void fraction(const double value) { brightness(static_cast<decltype(pin.bitsize.maximum)>(pin.bitsize.maximum * value)); }

		void off() const { pin = 0; }
		void off() { set(false); }
		void on() const { pin = bright; }
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