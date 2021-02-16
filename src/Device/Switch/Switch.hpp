#pragma once

#include "../../Output/OutputDigital.hpp"
#include "../../Pin/Pin.hpp"

namespace devuino
{
	namespace device
	{
		template<typename T>
		class Switch : public OutputDigital
		{
		  public:
			Switch(const T pin, const bool initial = false) : OutputDigital {initial}, pin {pin}
			{
				this->pin.initiate(devuino::pin::Output::Digital);
				set(initial);
			};

			~Switch()
			{
				set(false);
			};

			constexpr operator bool() const
			{
				return status;
			};

			void operator=(const bool value) const
			{
				set(value);
			};
			void operator=(const bool value)
			{
				status = value;
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

		  protected:
			T pin;

			void set(const bool value) const
			{
				pin.digital(value);
			};
		};
	}
}