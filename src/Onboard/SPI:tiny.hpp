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
		enum class Mode
		{
			SPI0,
			SPI1
		};
	};

	class SPItiny
	{
		template<typename DigitalBackendController>
		class Controller
		{
			template<typename DigitalBackendTransaction>
			class Transaction
			{
				devuino::device::Switch<DigitalBackendTransaction>& chipselect;

				uint8_t sendrecive(const uint8_t data) const
				{
					/* Copy data into transmission register */
					USIDR = data;

					/* Clear 'Counter Overflow Interrupt Flag' */
					USISR = (1 << USIOIF);

					// ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
					{
						while (!(USISR & (1 << USIOIF)))
						{
							USICR |= (1 << USITC);
						}
					}

					/* Return incomming data from peripheral */
					return USIBR;
				}

				void send(const uint8_t data) const
				{
					/* Copy data into transmission register */
					USIDR = data;

					/* Clear 'Counter Overflow Interrupt Flag' */
					USISR = (1 << USIOIF);

					// ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
					{
						while (!(USISR & (1 << USIOIF)))
						{
							USICR |= (1 << USITC);
						}
					}
				}

			  public:
				Transaction(devuino::device::Switch<DigitalBackendTransaction>& chipselect, const SPI::Mode mode) : chipselect {chipselect}
				{
					switch (mode)
					{
						case SPI::Mode::SPI1:
						{
							USICR |= (1 << USICS0);
							break;
						}

						case SPI::Mode::SPI0:
						default:
						{
							USICR &= ~(1 << USICS0);
							break;
						}
					}
				}

				void transfer(const uint8_t data) const
				{
					chipselect.off();
					send(data);
					chipselect.on();
				}

				void transfer(const uint8_t address, const uint8_t data) const
				{
					chipselect.off();
					send(address);
					send(data);
					chipselect.on();
				}

				uint8_t exchange(const uint8_t data) const
				{
					chipselect.off();
					const auto result = sendrecive(data);
					chipselect.on();

					return result;
				}

				uint8_t exchange(const uint8_t address, const uint8_t data) const
				{
					chipselect.off();
					send(address);
					const auto result = sendrecive(data);
					chipselect.on();

					return result;
				}
			};

			devuino::device::Switch<DigitalBackendController> chipselect;
			SPI::Mode mode;

		  public:
			Controller(DigitalBackendController&& chipselect, const SPI::Mode mode) : chipselect {devuino::move(chipselect)}, mode {mode}
			{
				this->chipselect.on();
			};

			constexpr auto transaction() { return Transaction<DigitalBackendController> {chipselect, mode}; }
		};

		bool valid = true;

	  public:
		constexpr SPItiny(volatile uint8_t& ddr, const uint8_t clock, const uint8_t output, const uint8_t input)
		{
			/* Select three-wire mode */
			USICR = (0 << USIWM1) | (1 << USIWM0);

			/* Disable 'Start Condition Interrupt' and 'Counter Overflow Interrupt' */
			USICR &= ~((1 << USISIE) | (1 << USIOIE));

			/* Set 'Clock Source: External, positive edge. 4-bit Counter Clock Source: Software clock strobe (USITC)' */
			USICR |= ((1 << USICS1) | (1 << USICLK));

			/* Set clock pin as output */
			ddr |= (1 << clock);
			/* Set output pin as output */
			ddr |= (1 << output);
			/* Set input pin as input */
			ddr &= ~(1 << input);
		}

		SPItiny(SPItiny&) = delete;
		SPItiny& operator=(SPItiny&) = delete;

		constexpr SPItiny(SPItiny&& other) noexcept { other.valid = false; }

		~SPItiny()
		{
			if (valid)
			{
				/* Disable USI */
				USICR = (0 << USIWM1) | (0 << USIWM0);
			}
		}

		[[nodiscard]] constexpr auto controller(auto&& chipselect, const SPI::Mode mode)
		{
			return Controller {devuino::move(chipselect), mode};
		}
	};
}