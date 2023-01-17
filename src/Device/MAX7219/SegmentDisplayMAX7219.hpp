/*
 * Datasheet (https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 * Archive (https://web.archive.org/https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 */

#pragma once

#include "../../Utilities/Display/SegmentDisplay/SevenSegmentString.hpp"
#include "../../Utilities/Iterator/Iterator.hpp"
#include "../../Utilities/Move/Move.hpp"
#include "../../Utilities/Resolution/Resolution.hpp"
#include "../../Utilities/String/Stringview.hpp"

#include <stdint.h>
#include <stdio.h>

namespace devuino::device
{
	template<typename SpiController>
	class MAX7219
	{
	  public:
		using DeviceString = devuino::utilities::SevenSegmentString<8, false>;

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
		decltype(bitsize.maximum) bright;
		bool status;
		bool valid = true;

	  public:
		constexpr MAX7219(SpiController&& spi, const bool initial = true, const DeviceString& string = {}) :

			spi {devuino::move(spi)}, bright {bitsize.maximum}, status {initial}
		{
			/* Reset display */
			brightness(bright);
			decode(Decode::None);
			scanlimit(Scanlimit::D01234567);
			test(false);
			print(string);
			power(initial);
		}

		MAX7219(MAX7219&) = delete;
		MAX7219& operator=(MAX7219&) = delete;

		constexpr MAX7219(MAX7219&& other) noexcept :
			spi {devuino::move(other.spi)}, bitsize {other.bitsize}, bright {other.bright}, status {other.status}
		{
			other.valid = false;
		}
		constexpr MAX7219& operator=(MAX7219&& other) noexcept
		{
			spi = devuino::move(other.spi);
			bitsize = other.bitsize;
			bright = other.bright;
			status = other.status;

			valid = true;
			other.valid = false;

			return *this;
		}

		~MAX7219()
		{
			if (valid)
			{
				test(false);
				power(false);
			}
		}

		constexpr void print(const devuino::utilities::Stringview string) { print(DeviceString {string}); }
		constexpr void print(const DeviceString& buffer)
		{
			auto transaction = spi.transaction();

			for (uint8_t index = 0; index < buffer.size(); index++)
			{
				transaction.transfer(index + 1, static_cast<uint8_t>(buffer[index]));
			}
		}

		/*  Test mode turns on all digits at full brightness.
			All programming is preserved while using this mode. */
		constexpr void test(const bool value)
		{
			auto transaction = spi.transaction();
			transaction.transfer(0x0f, value);
		}

		/* Set how many of the digits to decode using code-b */
		constexpr void decode(const Decode mode)
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

		/// @brief Set how many digit to display from memory
		/// @param limit Number of digits to show
		constexpr void scanlimit(const Scanlimit limit)
		{
			auto transaction = spi.transaction();
			transaction.transfer(0x0b, static_cast<uint8_t>(limit));
		}

		/// @brief Clear the digit memory
		constexpr void clear()
		{
			auto transaction = spi.transaction();

			for (uint8_t index = 1; index <= 8; index++)
			{
				transaction.transfer(index, 0);
			}
		}

		/// @brief Get brightness of display
		/// @return Current brightness in range [0..15]
		constexpr uint8_t brightness() const { return bright; }

		/// @brief Set brightness of display
		/// @param value New brightness in range [0..15]
		constexpr void brightness(const uint8_t value)
		{
			bright = value;

			auto transaction = spi.transaction();
			transaction.transfer(0x0a, value);
		}

		/// @brief Set brightness of display
		/// @param value New brightness in range [0..1]
		constexpr void fraction(const double value) { brightness(static_cast<uint8_t>(bitsize.maximum * value)); }

		/// @brief Turn off display and enter low-power mode. It is still possible to program the display while off
		constexpr void off() { set(false); }
		constexpr void on() { set(true); }

		constexpr void toggle() { set(!status); }

		/// @brief Turn display on or off. It is still possible to program the display while off
		constexpr void set(const bool value)
		{
			status = value;
			power(value);
		}

		/// @brief Update string to show on display
		/// @param string New string to show
		constexpr void operator=(const DeviceString& string) { print(string); }

		/// @brief Update string to show on display
		/// @param string New string to show
		constexpr void operator=(const devuino::utilities::Stringview string) { print(string); }

		/// @brief Get brightness resolution
		constexpr decltype(bitsize) resolution() const { return bitsize; }

	  private:
		/// @brief Turn display on or off. It is still possible to program the display while off
		constexpr void power(const bool value)
		{
			auto transaction = spi.transaction();
			transaction.transfer(0x0c, value);
		}
	};

	/// @brief Use if the compiler for some reason does not generate the SevenSegmentString at compile-time
	/// @param raw char* to character array
	/// @param i Size of character array
	constexpr devuino::utilities::SevenSegmentString<8, false> operator"" _max7219(const char* const raw, const size_t i)
	{
		return {devuino::utilities::Stringview {raw, i}};
	}
}