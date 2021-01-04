#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../Resolution/Resolution.hpp"

namespace devuino
{
	class Light
	{
	  public:
		constexpr Light(const Resolution bitresolution) : bitsize {bitresolution}, bright {bitresolution.maximum} {};

	  protected:
		Resolution bitsize;
		unsigned int bright;
	};
}

#endif
