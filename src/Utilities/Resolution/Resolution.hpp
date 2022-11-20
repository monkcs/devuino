#pragma once

#include <stdint.h>

namespace devuino::utilities
{
	enum class Bits
	{
		bits8,
		bits16,
		bits32,
		bits64
	};

	constexpr Bits calculate(unsigned int bits)
	{
		return (bits <= 8) ? Bits::bits8 : (bits <= 16) ? Bits::bits16 : (bits <= 32) ? Bits::bits32 : Bits::bits64;
	}

	template<Bits size>
	struct Storage;

	template<>
	struct Storage<Bits::bits8>
	{
		using type = uint_least8_t;
	};

	template<>
	struct Storage<Bits::bits16>
	{
		using type = uint_least16_t;
	};

	template<>
	struct Storage<Bits::bits32>
	{
		using type = uint_least32_t;
	};

	template<>
	struct Storage<Bits::bits64>
	{
		using type = uint_least64_t;
	};

	template<int bitsize>
	struct Resolution
	{
		static_assert(bitsize > 0, "Number of bits needs to be larger than zero.");
		static_assert(bitsize < 64, "Number of bits needs to be smaller or equal to 63.");

	  public:
		uint8_t bits = static_cast<uint8_t>(bitsize);
		typename Storage<calculate(bitsize)>::type maximum;

		/* Calculate the maximum value, provided the number of bits in template parameter */
		constexpr Resolution() : maximum {static_cast<decltype(maximum)>((static_cast<uint_least64_t>(1) << bitsize) - 1)} { }
	};
}
