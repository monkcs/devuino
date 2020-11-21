#ifndef LEDRGB_H
#define LEDRGB_H

#include "../../Light/Rgb.h"
#include "../../Output/OutputDigital.h"
#include "../../Pin/Pin.h"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class LedRgb : public OutputDigital, public Rgb
		{
		  public:
			LedRgb(const T redpin, const T greenpin, const T bluepin, const Colour colours = {0, 0, 0}, const bool initial = false) : OutputDigital {initial}, Rgb {colours}, pins {redpin, greenpin, bluepin}
			{
				for (auto& pin : pins)
				{
					pin.initiate(pin::Output::Analog);
				}

				update();
			}
			~LedRgb()
			{
				off();
			}

			void operator=(const bool value)
			{
				status = value;
				set(value);
			}

			void update() const override
			{
				if (status)
				{
					const double fraction = static_cast<double>(bright) / static_cast<double>(bitsize.maximum);

					for (auto index = 0; index < 3; index++)
					{
						const uint8_t calculated = static_cast<uint8_t>(colours[index] * fraction);
						pins[index].analogwrite(calculated);
					}
				}
				else
				{
					for (auto& pin : pins)
					{
						pin.analogwrite(0);
					}
				}
			}

		  private:
			T pins[3];

			void set(const bool value) override
			{
				update();
			}
		};
	}
}

#endif
