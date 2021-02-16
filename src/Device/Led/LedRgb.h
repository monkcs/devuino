#pragma once

#include "../../Light/Rgb.h"
#include "../../Output/OutputDigital.hpp"
#include "../../Pin/Pin.hpp"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class LedRgb : public OutputDigital, public Rgb
		{
		  public:
			LedRgb(const T pins[3], const Colour colours = Colour {}, const bool initial = false) : LedRgb<T> {{pins[0], pins[1], pins[2]}, colours, initial} {};
			LedRgb(const T redpin, const T greenpin, const T bluepin, const Colour colours = Colour {}, const bool initial = false) : OutputDigital {initial}, Rgb {colours}, pins {redpin, greenpin, bluepin}
			{
				for (auto& pin : pins)
				{
					pin.initiate(pin::Output::Analog);
				}

				set(initial);
			};

			~LedRgb()
			{
				set(false);
			}

			void operator=(const bool value)
			{
				status = value;
				set(value);
			};
			void operator=(const bool value) const
			{
				set(value);
			};

			void off() const
			{
				operator=(false);
			};
			void off()
			{
				operator=(false);
			};

			void on() const
			{
				operator=(true);
			};
			void on()
			{
				operator=(true);
			};

			void toggle()
			{
				operator=(!status);
			};

			void brightness(const unsigned int value)
			{
				bright = value;
				set(status);
			};

			void fraction(const double value)
			{
				brightness(static_cast<unsigned int>(bitsize.maximum * value));
			};

		  protected:
			T pins[3];

			void set(const bool value) const
			{
				// TODO Make precompiled colours
				if (value)
				{
					const double fraction = static_cast<double>(bright) / bitsize.maximum;

					for (uint8_t index = 0; index < 3; index++)
					{
						const uint8_t calculated = static_cast<uint8_t>(colours[index] * fraction);
						pins[index].analog(calculated);
					}
				}
				else
				{
					for (uint8_t index = 0; index < 3; index++)
					{
						pins[index].analog(0);
					}
				}
			}
		};
	}
}
