#ifndef LED_H
#define LED_H

#include "../../Light/Light.h"
#include "../../Output/OutputDigital.h"
#include "../../Pin/Pin.h"
#include "../../Resolution/Resolution.h"

namespace devuino
{
	namespace device
	{
		template<class T>
		class Led final : public Light, public OutputDigital
		{
		  public:
			Led(const T pin, const bool initial = false, const Resolution bitresolution = Resolution(8)) : Light {bitresolution}, OutputDigital {initial}, pin {pin}
			{
				this->pin.initiate(pin::Output::Analog);
				set(initial);
			};

			~Led()
			{
				set(false);
			};

			void operator=(const bool value)
			{
				value ? on() : off();
			};
			void operator=(const bool value) const
			{
				set(value);
			};

			unsigned int brightness() const override
			{
				return bright;
			};

			void brightness(const unsigned int value) override
			{
				bright = value;
				set(status);
			};

		  protected:
			T pin;

			void set(const bool value) const override
			{
				pin.analogwrite(value ? bright : 0);
			}
		};
	}
}
#endif
