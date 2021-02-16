#pragma once

namespace devuino
{
	class OutputDigital
	{
	  public:
		constexpr OutputDigital(const bool initial) : status {initial} {};

		/* Example operator= to use in final class */
		/*
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
			operator=(status);
		}; */

	  protected:
		bool status;
	};
}
