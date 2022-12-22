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
		constexpr LightRgb(const AnalogBackend pins[3], const Colour colours = Colour {}, const bool initial = false) :
			LightRgb<AnalogBackend> {{pins[0], pins[1], pins[2]}, colours, initial} {};

		constexpr LightRgb(const AnalogBackend redpin,
						   const AnalogBackend greenpin,
						   const AnalogBackend bluepin,
						   const Colour colours = Colour {},
						   const bool initial = false) :
			red {Light<AnalogBackend> {redpin, initial, colours.red}},
			green {Light<AnalogBackend> {greenpin, initial, colours.green}},
			blue {Light<AnalogBackend> {bluepin, initial, colours.blue}} {};

		~LightRgb() { set(false); }

		Light<AnalogBackend> red;
		Light<AnalogBackend> green;
		Light<AnalogBackend> blue;

		constexpr operator Colour() const
		{
			return {static_cast<uint8_t>(red.brightness()), static_cast<uint8_t>(green.brightness()),
					static_cast<uint8_t>(blue.brightness())};
		}

		constexpr LightRgb& operator=(const Colour colours)
		{
			colour(colours);
			return *this;
		}

		constexpr const Light<AnalogBackend>& operator[](const uint8_t index) const
		{
			return (index == 0) ? red : ((index == 1) ? green : blue);
		}
		constexpr Light<AnalogBackend>& operator[](const uint8_t index) { return (index == 0) ? red : ((index == 1) ? green : blue); }

		constexpr void off() { set(false); }
		constexpr void on() { set(true); }

		constexpr void toggle()
		{
			red.toggle();
			green.toggle();
			blue.toggle();
		}

		constexpr void colour(const Colour colours)
		{
			red = colours.red;
			green = colours.green;
			blue = colours.blue;
		}

		constexpr void brightness(const uint8_t value)
		{
			red.brightness(value);
			green.brightness(value);
			blue.brightness(value);
		}

		constexpr void fraction(const double value)
		{
			red.fraction(value);
			green.fraction(value);
			blue.fraction(value);
		}

		constexpr void set(const bool value)
		{
			red.set(value);
			green.set(value);
			blue.set(value);
		}

		constexpr decltype(red.resolution()) resolution() const { return red.resolution(); }
	};
}
