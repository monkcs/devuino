#ifndef LED_HPP
#define LED_HPP

#include "../../Light/Light.hpp"
#include "../../Output/OutputDigital.hpp"
#include "../../Pin/Pin.hpp"
#include "../../Resolution/Resolution.hpp"

namespace devuino
{
	namespace device
	{
		template<class T>
		class Led : public Light, public OutputDigital
		{
		  public:
			Led(const T pin, const bool initial = false, const Resolution bitresolution = Resolution {8}) : Light {bitresolution}, OutputDigital {initial}, pin {pin}
			{
				if (bitsize.bits > 1)
				{
					this->pin.initiate(devuino::pin::Output::Analog);
				}
				else
				{
					this->pin.initiate(devuino::pin::Output::Digital);
				}

				set(initial);
			};

			~Led()
			{
				set(false);
			};

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
			T pin;

			void set(const bool value) const
			{
				if (bitsize.bits > 1)
				{
					pin.analog(value ? bright : 0);
				}
				else
				{
					pin.digital(value);
				}
			}
		};
	}
}
#endif
