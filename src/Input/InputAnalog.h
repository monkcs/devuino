#ifndef INPUTANALOG_H
#define INPUTANALOG_H

#include "../Resolution/Resolution.h"

namespace devuino
{
	class InputAnalog
	{
	  public:
		InputAnalog(const Resolution bitresolution, const bool debounce) : bitsize(bitresolution), debounce(debounce) {};

		[[nodiscard]] double percent() const
		{
			return static_cast<double>(value()) / static_cast<double>(bitsize.maximum);
		};

		virtual int value() const = 0;

	  protected:
		Resolution bitsize;
		bool debounce;
	};
}

#endif
