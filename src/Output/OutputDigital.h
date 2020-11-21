#ifndef OUTPUTDIGITAL_H
#define OUTPUTDIGITAL_H

namespace devuino
{
	class OutputDigital
	{
	  public:
		constexpr OutputDigital(const bool initial) : status {initial} {};

		void off()
		{
			status = false;
			set(false);
		};
		void off() const
		{
			set(false);
		};

		void on()
		{
			status = true;
			set(true);
		};
		void on() const
		{
			set(true);
		};

		void toggle()
		{
			status ? off() : on();
		};

		/* Example operator= to use in final class */
		void operator=(const bool value)
		{
			status = value;
			set(value);
		};
		void operator=(const bool value) const
		{
			set(value);
		};

	  protected:
		virtual void set(const bool value) const = 0;
		bool status;
	};
}

#endif
