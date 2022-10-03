/*
 * Datasheet (https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 * Archive (https://web.archive.org/https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 */

#pragma once

#include "../../Display/CharacterDisplay/SegmentDisplay/SevenSegmentString.hpp"
#include "../../Display/Direction.hpp"
#include "../../Interface/SPI.h"
#include "../../Resolution/Resolution.hpp"
#include "../../Tools/Iterator.hpp"

#include <stdint.h>
#include <stdio.h>

namespace devuino::device
{
	// TODO: Implement support for multiple units
	template<typename ChipSelect>	 //, unsigned int units = 1>
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

		MAX7219(const devuino::interface::spi::Controller<ChipSelect> spi,
				const bool initial = true,
				const SevenSegmentString<8> buffer = {}) :
			buffer {buffer},
			spi {spi},
			bitsize {4},
			bright {static_cast<uint8_t>(bitsize.maximum)},
			decoding {Decode::None},
			status {initial}
		{
			/* Reset display */
			brightness(bright);
			decode(decoding);
			clear();
			scanlimit(Scanlimit::D01234567);
			test(false);
			set(status);
		};

		~MAX7219()
		{
			test(false);
			off();
		}

		void print() const
		{
			// TODO: Implement support for multiple units

			uint8_t index {8};

			for (const auto& character : buffer)
			{
				spi.transfer(index, static_cast<uint8_t>(character));
				--index;
			}

			/*
			for (uint8_t i = 0; i < units * 8; i++)
			{
				spi.transfer(i + 1, buffer[(units * 8 - 1) - i]);
			}
			*/
		}

		/*  Test mode turns on all digits at full brightness.
			All programming is preserved while using this mode. */
		void test(const bool value) const { spi.transfer(0x0f, value); };

		/* Set how many of the digits to decode using code-b */
		void decode(const Decode mode)
		{
			decoding = mode;

			switch (mode)
			{
				case Decode::D0123:
				{
					spi.transfer(0x09, 0x0f);
					break;
				}

				case Decode::D01234567:
				{
					spi.transfer(0x09, 0xff);
					break;
				}

				default:
				{
					spi.transfer(0x09, static_cast<uint8_t>(mode));
					break;
				}
			}
		}

		/* Set how many digit to display from memory. */
		void scanlimit(const Scanlimit limit) const { spi.transfer(0x0b, static_cast<uint8_t>(limit)); };

		void clear()
		{
			buffer.clear();
			print();
		};

		constexpr uint8_t brightness() const { return bright; };
		void brightness(const uint8_t value)
		{
			bright = value;
			spi.transfer(0x0a, value);
		};

		void fraction(const double value) { brightness(static_cast<uint8_t>(bitsize.maximum * value)); };

		void off() const { set(false); };
		void off() { set(false); };

		void on() const { set(true); };
		void on() { set(true); };

		void toggle() { set(!status); };

		/* 	Turn on or off the display to enter low-power mode.
			It is still possible to program the display in power-off mode. */
		void set(const bool value) const { spi.transfer(0x0c, value); }

		/* 	Turn on or off the display to enter low-power mode.
			It is still possible to program the display in power-off mode. */
		void set(const bool value)
		{
			status = value;
			spi.transfer(0x0c, value);
		}

		void operator=(const tools::Stringview& string)
		{
			buffer = string;
			print();
		}

		SevenSegmentCharacter operator[](const size_t position) const { return buffer[position]; }
		SevenSegmentCharacter& operator[](const size_t position) { return buffer[position]; }

		tools::Iterator<const SevenSegmentCharacter> begin() const { return buffer.begin(); }
		tools::Iterator<const SevenSegmentCharacter> end() const { return buffer.end(); }
		tools::Iterator<SevenSegmentCharacter> begin() { return buffer.begin(); }
		tools::Iterator<SevenSegmentCharacter> end() { return buffer.end(); }

		SevenSegmentString</*units * */ 8> buffer;

	  protected:
		devuino::interface::spi::Controller<ChipSelect> spi;
		Resolution bitsize;
		uint8_t bright;
		Decode decoding;
		bool status;

		void set() const { set(status); }
	};
}