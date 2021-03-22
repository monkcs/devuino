#pragma once

namespace devuino
{
	class OutputDigital
	{
	  public:
		constexpr OutputDigital(const bool initial) : status {initial} {};

		/* For use in derived class
			constexpr operator bool() { return status; };

			void operator=(const bool value) const { set(value); };
			void operator=(const bool value) { set(value); };
		*/

		void off() const { set(false); };
		void off() { set(false); };

		void on() const { set(true); };
		void on() { set(true); };

		void toggle() { set(!status); };

	  protected:
		bool status;

		virtual void set(const bool value) const = 0;
		virtual void set(const bool value) = 0;
	};
}
