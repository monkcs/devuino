#pragma once

#include "../../Light/Colour.hpp"
#include "../../Pin/Pin.hpp"
#include "Light.hpp"

namespace devuino::device
{
	template<typename Type>
	class LightRgb
	{
	  public:
		LightRgb(const Type pins[3], const Colour colours = Colour {}, const bool initial = false) :
			LightRgb<Type> {{pins[0], pins[1], pins[2]}, colours, initial} {};

		LightRgb(const Type redpin, const Type greenpin, const Type bluepin, const Colour colours = Colour {}, const bool initial = false) :
			red {Light<Type> {redpin, colours.red, initial, Resolution {8}}},
			green {Light<Type> {greenpin, colours.green, initial, Resolution {8}}},
			blue {Light<Type> {bluepin, colours.blue, initial, Resolution {8}}} {};

		~LightRgb() { set(false); }

		Light<Type> red;
		Light<Type> green;
		Light<Type> blue;

		constexpr operator Colour() const
		{
			return {static_cast<uint8_t>(red.brightness()), static_cast<uint8_t>(green.brightness()),
					static_cast<uint8_t>(blue.brightness())};
		};

		void operator=(const Colour colours) { colour(colours); };

		const Light<Type>& operator[](const uint8_t index) const { return (index == 0) ? red : ((index == 1) ? green : blue); };
		Light<Type>& operator[](const uint8_t index) { return (index == 0) ? red : ((index == 1) ? green : blue); };

		void off() const { set(false); };
		void off() { set(false); };

		void on() const { set(true); };
		void on() { set(true); };

		void toggle()
		{
			red.toggle();
			green.toggle();
			blue.toggle();
		};

		void colour(const Colour colours)
		{
			red = colours.red;
			green = colours.green;
			blue = colours.blue;
		};

		void brightness(const uint8_t value)
		{
			red.brightness(value);
			green.brightness(value);
			blue.brightness(value);
		};

		void fraction(const double value)
		{
			red.fraction(value);
			green.fraction(value);
			blue.fraction(value);
		};

		void set(const bool value) const
		{
			red.set(value);
			green.set(value);
			blue.set(value);
		}
		void set(const bool value)
		{
			red.set(value);
			green.set(value);
			blue.set(value);
		}
	};
}
