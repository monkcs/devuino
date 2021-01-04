#ifndef RESOLUTION_HPP
#define RESOLUTION_HPP

#include <stdint.h>

namespace devuino
{
	class Resolution
	{
	  public:
		/* Set the bits and compute the resolution with a cap on 15 bits,
		   (because currently we are using a uint16_t to return it. */

		explicit constexpr Resolution(const uint8_t bit) : bits {guard(bit)}, maximum {maxvalue(bit)} {};

		uint8_t bits;
		uint16_t maximum;

	  protected:
		constexpr uint8_t guard(const uint8_t bit) const
		{
			return (bit < 15) ? bit : static_cast<uint8_t>(15);
		};

		constexpr uint16_t maxvalue(const uint8_t bit) const
		{
			return (1 << guard(bit)) - 1;
		};
	};
}

#endif
