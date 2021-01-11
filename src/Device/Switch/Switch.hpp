#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "../../Pin/Pin.hpp"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class Switch
		{
		  public:
			Switch(const T pin, const bool initial = false) : pin {pin}
			{
				this->pin.initiate(devuino::pin::Output::Digital);
				set(initial);
			};

			~Switch()
			{
				set(false);
			};

			void operator=(const bool value) const
			{
				set(value);
			};

			void off() const
			{
				operator=(false);
			};

			void on() const
			{
				operator=(true);
			};

			void toggle() const
			{
				pin.digitaltoggle();
			};

		  protected:
			T pin;

			void set(const bool value) const
			{
				pin.digital(value);
			};
		};
	}
}
#endif