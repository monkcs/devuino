#pragma once

#include "../Resolution/Resolution.hpp"

namespace devuino
{
	class InputAnalog
	{
	  public:
		InputAnalog(const Resolution bitresolution, const bool debounce) : bitsize {bitresolution}, debounce {debounce} {};

		/*
		double fraction() const
		{
			return static_cast<double>(value()) / static_cast<double>(bitsize.maximum);
		};

		virtual int value() const = 0;
		*/

	  protected:
		Resolution bitsize;
		bool debounce;
	};
}
