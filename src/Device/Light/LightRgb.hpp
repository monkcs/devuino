#pragma once

#include "../../Onboard/Pin.hpp"
#include "../../Utilities/Light/Colour.hpp"
#include "Light.hpp"

namespace devuino::device
{
	using devuino::utilities::Resolution;

	template<typename AnalogBackend = devuino::onboard::AnalogOutput>
	class LightRgb
	{
	  public:
		LightRgb(const AnalogBackend pins[3], const Colour colours = Colour {}, const bool initial = false) :
			LightRgb<AnalogBackend> {{pins[0], pins[1], pins[2]}, colours, initial} {};

		LightRgb(const AnalogBackend redpin,
				 const AnalogBackend greenpin,
				 const AnalogBackend bluepin,
				 const Colour colours = Colour {},
				 const bool initial = false) :
			red {Light<AnalogBackend> {redpin, colours.red, initial, Resolution {8}}},
			green {Light<AnalogBackend> {greenpin, colours.green, initial, Resolution {8}}},
			blue {Light<AnalogBackend> {bluepin, colours.blue, initial, Resolution {8}}} {};

		~LightRgb() { set(false); }

		Light<AnalogBackend> red;
		Light<AnalogBackend> green;
		Light<AnalogBackend> blue;

		constexpr operator Colour() const
		{
			return {static_cast<uint8_t>(red.brightness()), static_cast<uint8_t>(green.brightness()),
					static_cast<uint8_t>(blue.brightness())};
		}

		LightRgb& operator=(const Colour colours)
		{
			colour(colours);
			return *this;
		}

		const Light<AnalogBackend>& operator[](const uint8_t index) const { return (index == 0) ? red : ((index == 1) ? green : blue); }
		Light<AnalogBackend>& operator[](const uint8_t index) { return (index == 0) ? red : ((index == 1) ? green : blue); }

		void off() { set(false); }
		void on() { set(true); }

		void toggle()
		{
			red.toggle();
			green.toggle();
			blue.toggle();
		}

		void colour(const Colour colours)
		{
			red = colours.red;
			green = colours.green;
			blue = colours.blue;
		}

		void brightness(const uint8_t value)
		{
			red.brightness(value);
			green.brightness(value);
			blue.brightness(value);
		}

		void fraction(const double value)
		{
			red.fraction(value);
			green.fraction(value);
			blue.fraction(value);
		}

		void set(const bool value)
		{
			red.set(value);
			green.set(value);
			blue.set(value);
		}
	};
}
