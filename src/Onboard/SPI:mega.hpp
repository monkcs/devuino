#pragma once

#include "../Device/Switch/Switch.hpp"
#include "../Utilities/Move/Move.hpp"
#include "Digital.hpp"

#include <stdint.h>
#include <util/atomic.h>

namespace devuino::onboard
{
	class SPI
	{
	  public:
		enum class Mode : uint8_t
		{
			SPI0,
			SPI1,
			SPI2,
			SPI3
		};

		enum class DataOrder : uint8_t
		{
			MSB = 0,
			LSB = 1
		};

		enum class Clock : uint8_t
		{
			Divide2 = (1 << SPI2X) | (0 << SPR1) | (0 << SPR0),
			Divide4 = (0 << SPI2X) | (0 << SPR1) | (0 << SPR0),
			Divide8 = (1 << SPI2X) | (0 << SPR1) | (1 << SPR0),
			Divide16 = (0 << SPI2X) | (0 << SPR1) | (1 << SPR0),
			Divide32 = (1 << SPI2X) | (1 << SPR1) | (0 << SPR0),
			Divide64 = (0 << SPI2X) | (1 << SPR1) | (0 << SPR0),
			Divide128 = (0 << SPI2X) | (1 << SPR1) | (1 << SPR0)
		};

		struct Configuration
		{
			SPI::Mode mode = SPI::Mode::SPI0;
			SPI::Clock clock = SPI::Clock::Divide2;
			SPI::DataOrder dataorder = SPI::DataOrder::MSB;

			constexpr uint8_t controlbitmask() const
			{
				uint8_t result = 0;

				switch (mode)
				{
					case SPI::Mode::SPI1:
					{
						result |= (1 << CPHA);
						break;
					}
					case SPI::Mode::SPI2:
					{
						result |= (1 << CPOL);
						break;
					}
					case SPI::Mode::SPI3:
					{
						result |= (1 << CPOL) | (1 << CPHA);
						break;
					}
					default: break;
				}

				result |= (static_cast<uint8_t>(clock) & static_cast<uint8_t>(~(1 << 2)));
				result |= (static_cast<uint8_t>(dataorder) << DORD);

				return result;
			}

			constexpr uint8_t statusbitmask() const { return static_cast<uint8_t>(clock) >> 2; }
		};
	};

	class SPImega
	{
		template<typename DigitalBackendController>
		class Controller
		{
			template<typename DigitalBackendTransaction>
			class Transaction
			{
				devuino::device::Switch<DigitalBackendTransaction>& chipselect;

				constexpr uint8_t sendrecive(const uint8_t data) const
				{
					send(data);

					/* Return incomming data from peripheral */
					return SPDR;
				}

				constexpr void send(const uint8_t data) const
				{
					/* Copy data into transmission register */
					SPDR = data;

					/* Wait for transmission complete */
					while (!(SPSR & (1 << SPIF))) { }
				}

			  public:
				constexpr Transaction(devuino::device::Switch<DigitalBackendTransaction>& chipselect) : chipselect {chipselect} { }

				constexpr void transfer(const uint8_t data) const
				{
					chipselect.off();
					send(data);
					chipselect.on();
				}

				constexpr void transfer(const uint8_t address, const uint8_t data) const
				{
					chipselect.off();
					send(address);
					send(data);
					chipselect.on();
				}

				constexpr uint8_t exchange(const uint8_t data) const
				{
					chipselect.off();
					const auto result = sendrecive(data);
					chipselect.on();

					return result;
				}

				constexpr uint8_t exchange(const uint8_t address, const uint8_t data) const
				{
					chipselect.off();
					send(address);
					const auto result = sendrecive(data);
					chipselect.on();

					return result;
				}
			};

			devuino::device::Switch<DigitalBackendController> chipselect;

		  public:
			constexpr Controller(DigitalBackendController&& chipselect, const SPI::Configuration configuration) :
				chipselect {devuino::move(chipselect)}
			{
				this->chipselect.on();

				/* Set MOSI and SCK as output */
				DDRB |= (1 << PINB3) | (1 << PINB5);

				/* Set hardware chip-select as output, otherwise SPI controller may be disabled */
				DDRB |= (1 << PINB2);

				/* Enable SPI, set configuration */
				SPCR = configuration.controlbitmask() | (1 << SPE) | (1 << MSTR);
				SPSR = configuration.statusbitmask();
			};

			constexpr auto transaction() { return Transaction<DigitalBackendController> {chipselect}; }
		};

		bool valid = true;

	  public:
		constexpr SPImega() { }
		~SPImega()
		{
			if (valid)
			{
				/* Disable SPI */
				SPCR &= ~(1 << SPE);
			}
		}

		SPImega(SPImega&) = delete;
		SPImega& operator=(SPImega&) = delete;

		constexpr SPImega(SPImega&& other) noexcept { other.valid = false; }
		constexpr SPImega& operator=(SPImega&& other) noexcept
		{
			valid = true;
			other.valid = false;

			return *this;
		}

		[[nodiscard]] constexpr auto controller(auto&& chipselect, const SPI::Configuration configuration = {}) const
		{
			return Controller {devuino::move(chipselect), configuration};
		}
	};
}