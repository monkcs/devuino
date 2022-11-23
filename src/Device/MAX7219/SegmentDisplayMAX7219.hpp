/*
 * Datasheet (https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 * Archive (https://web.archive.org/https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 */

#pragma once

#include "../../Utilities/Display/SegmentDisplay/SevenSegmentString.hpp"
#include "../../Utilities/Iterator/Iterator.hpp"
#include "../../Utilities/Resolution/Resolution.hpp"
#include "../../Utilities/String/Stringview.hpp"

#include <stdint.h>
#include <stdio.h>

namespace devuino::device
{
	// TODO: Implement support for multiple units
	template<typename SpiController>
	class MAX7219
	{
	  public:
		enum class Decode : uint8_t
		{
			None = 0,
			D0 = 1,
			D0123 = 4,
			D01234567 = 8
		};

		enum class Scanlimit : uint8_t
		{
			D0 = 0,
			D01 = 1,
			D012 = 2,
			D0123 = 3,
			D01234 = 4,
			D012345 = 5,
			D0123456 = 6,
			D01234567 = 7,
		};

	  private:
		SpiController spi;
		Resolution<4> bitsize {};
		uint8_t bright;
		bool status;

	  public:
		SevenSegmentString<8> buffer;

		MAX7219(const SpiController spi, const bool initial = true, const Stringview string = {}) :

			spi {spi}, bright {static_cast<uint8_t>(bitsize.maximum)}, status {initial}, buffer {string}
		{
			/* Reset display */
			brightness(bright);
			decode(Decode::None);
			scanlimit(Scanlimit::D01234567);
			test(false);
			print();
			set(initial);
		}

		~MAX7219()
		{
			test(false);
			off();
		}

		void print()
		{
			auto transaction = spi.transaction();

			uint8_t index {8};
			for (const auto character : buffer)
			{
				transaction.transfer(index, static_cast<uint8_t>(character));
				--index;
			}
		}

		/*  Test mode turns on all digits at full brightness.
			All programming is preserved while using this mode. */
		void test(const bool value)
		{
			auto transaction = spi.transaction();
			transaction.transfer(0x0f, value);
		}

		/* Set how many of the digits to decode using code-b */
		void decode(const Decode mode)
		{
			auto transaction = spi.transaction();

			switch (mode)
			{
				case Decode::D0123:
				{
					transaction.transfer(0x09, 0x0f);
					break;
				}

				case Decode::D01234567:
				{
					transaction.transfer(0x09, 0xff);
					break;
				}

				default:
				{
					transaction.transfer(0x09, static_cast<uint8_t>(mode));
					break;
				}
			}
		}

		/* Set how many digit to display from memory. */
		void scanlimit(const Scanlimit limit)
		{
			auto transaction = spi.transaction();
			transaction.transfer(0x0b, static_cast<uint8_t>(limit));
		}

		void clear()
		{
			buffer.clear();
			print();
		}

		constexpr uint8_t brightness() const { return bright; }
		void brightness(const uint8_t value)
		{
			bright = value;

			auto transaction = spi.transaction();
			transaction.transfer(0x0a, value);
		}

		void fraction(const double value) { brightness(static_cast<uint8_t>(bitsize.maximum * value)); }

		void off() { set(false); }
		void on() { set(true); }

		void toggle() { set(!status); }

		/* 	Turn on or off the display to enter low-power mode.
			It is still possible to program the display in power-off mode. */
		void set(const bool value)
		{
			status = value;

			auto transaction = spi.transaction();
			transaction.transfer(0x0c, value);
		}

		constexpr void operator=(const SevenSegmentString<8> string)
		{
			buffer = string;
			print();
		}

		void operator=(const devuino::utilities::Stringview string)
		{
			buffer = string;
			print();
		}

		constexpr SevenSegmentCharacter operator[](const size_t position) const { return buffer[position]; }
		constexpr SevenSegmentCharacter& operator[](const size_t position) { return buffer[position]; }

		constexpr devuino::utilities::Iterator<const SevenSegmentCharacter> begin() const { return buffer.begin(); }
		constexpr devuino::utilities::Iterator<const SevenSegmentCharacter> end() const { return buffer.end(); }
		constexpr devuino::utilities::Iterator<SevenSegmentCharacter> begin() { return buffer.begin(); }
		constexpr devuino::utilities::Iterator<SevenSegmentCharacter> end() { return buffer.end(); }

		constexpr decltype(bitsize) resolution() const { return bitsize; }
	};
}