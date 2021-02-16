#pragma once

namespace devuino
{
	class InputDigital
	{
	  public:
		InputDigital(const bool debounce) : debounce(debounce) {};

		// virtual bool value() const = 0;

	  protected:
		bool debounce;
	};
}