#pragma once

namespace devuino
{
	class InputDigital
	{
	  public:
		InputDigital(const bool debounce) : debounce {debounce} {};

		/* For use in derived class
			operator bool() const { return value(); };
		*/

		virtual bool value() const = 0;

	  protected:
		bool debounce;
	};
}