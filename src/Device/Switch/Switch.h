#ifndef SWITCH_H
#define SWITCH_H

#include "../../Output/OutputDigital.h"

namespace devuino
{
	namespace device
	{
		template<class T>
		class Switch : public OutputDigital
		{
		  public:
			Switch(const T pin, const bool initial = false) : OutputDigital {initial}, pin {pin}
			{
				this->pin.initiate(pin::Output::Digital);
				set(initial);
			};

			~Switch()
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

			void toggle()
			{
				operator=(!status);
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
