#pragma once

#include "../../Device/EEPROM/EEPROM.hpp"
#include "../Analog.hpp"
#include "../Digital.hpp"
#include "../EepromBackend:tiny:mega.hpp"
#include "../SPI:tiny.hpp"

#include <Arduino.h>

namespace devuino::onboard
{
	template<int flash_size, int eeprom_size, int sram_size>
	class ATtinyX5
	{
	  public:
		enum class Trigger : uint8_t
		{
			Low = (0 << ISC01) | (0 << ISC00),
			Change = (0 << ISC01) | (1 << ISC00),
			FallingEdge = (1 << ISC01) | (0 << ISC00),
			RisingEdge = (1 << ISC01) | (1 << ISC00)
		};

	  private:
		class Analog
		{
		  public:
			/// Low-level access to analog output pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto output(const int pin) { return AnalogOutput {static_cast<uint8_t>(pin)}; }

			/// Low-level access to analog input pin onboard device.
			/// @param pin Arduino analog pin numbering.
			[[nodiscard]] auto input(const int pin)
			{
				switch (pin)
				{
					case A1: return AnalogInput {static_cast<uint8_t>(pin), PB2, DDRB};
					case A2: return AnalogInput {static_cast<uint8_t>(pin), PB4, DDRB};
					case A3: return AnalogInput {static_cast<uint8_t>(pin), PB3, DDRB};

					case A0:
					default: return AnalogInput {static_cast<uint8_t>(pin), PB5, DDRB};
				}
			}
		};

		class Digital
		{
		  public:
			/// Low-level access to digital output pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto output(const int pin)
			{
				switch (pin)
				{
					case 1: return DigitalOutput {PB1, PORTB, DDRB};
					case 2: return DigitalOutput {PB2, PORTB, DDRB};
					case 3: return DigitalOutput {PB3, PORTB, DDRB};
					case 4: return DigitalOutput {PB4, PORTB, DDRB};
					case 5: return DigitalOutput {PB5, PORTB, DDRB};

					case 0:
					default: return DigitalOutput {PB0, PORTB, DDRB};
				}
			}

			/// Low-level access to digital input pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto input(const int pin)
			{
				switch (pin)
				{
					case 1: return DigitalInput {PB1, PORTB, PINB, DDRB};
					case 2: return DigitalInput {PB2, PORTB, PINB, DDRB};
					case 3: return DigitalInput {PB3, PORTB, PINB, DDRB};
					case 4: return DigitalInput {PB4, PORTB, PINB, DDRB};
					case 5: return DigitalInput {PB5, PORTB, PINB, DDRB};

					case 0:
					default: return DigitalInput {PB0, PORTB, PINB, DDRB};
				}
			}
		};

		class Interrupt
		{
			class PinChange
			{
				class PinChangePin
				{
					volatile uint8_t& channel;
					uint8_t bitmask;

				  public:
					constexpr PinChangePin(volatile uint8_t& channel, const uint8_t bit) :
						channel {channel}, bitmask {static_cast<uint8_t>(1 << bit)}
					{
					}

					/// @brief Attach pin for interrupt on pin change
					constexpr void attach() { channel |= bitmask; }

					/// @brief Detach pin for interrupt on pin change
					constexpr void detach() { channel &= ~bitmask; }
				};

			  public:
				/// @brief Access to pin change interrupt, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5),
				/// (whole PORTB).
				/// @param interrupt Pin change using PCINTx numbering
				[[nodiscard]] constexpr PinChangePin pin(const int interrupt)
				{
					switch (interrupt)
					{
						case 1: return PinChangePin {PCMSK, PCINT1};
						case 2: return PinChangePin {PCMSK, PCINT2};
						case 3: return PinChangePin {PCMSK, PCINT3};
						case 4: return PinChangePin {PCMSK, PCINT4};
						case 5: return PinChangePin {PCMSK, PCINT5};

						case 0:
						default: return PinChangePin {PCMSK, PCINT0};
					}
				}

				/// Enable interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5),
				/// (whole PORTB).
				constexpr void enable() { GIMSK |= (1 << PCIE); }

				/// Disable interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5),
				/// (whole PORTB).
				constexpr void disable() { GIMSK &= ~(1 << PCIE); }
			};

			class External
			{
			  public:
				/// Attach interrupt INT0, located on physical pin 7.
				/// @param trigger Condition that will trigger an interrupt.
				void attach(const Trigger trigger)
				{
					MCUCR |= static_cast<uint8_t>(trigger);
					GIMSK |= (1 << INT0);
				}

				/// Detach interrupt INT0, located on physical pin 7.
				void detach() { GIMSK &= ~(1 << INT0); }
			};

		  public:
			/// Interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5), (whole PORTB).
			PinChange pinchange {};

			/// Interrupt INT0, located on physical pin 7.
			External external {};

			/// Enable global interrupts
			void enable() const { sei(); }

			/// Disable global interrupts
			void disable() const { cli(); }
		};

		/// @brief Universal Serial Interface
		class USI
		{
		  public:
			USI(const USI&) = delete;
			USI& operator=(const USI&) = delete;

			[[nodiscard]] SPItiny spi() { return SPItiny {DDRB, PB2, PB1, PB0}; }
		};

		class Port
		{
			/// @brief Global pull-up resistor control
			class PullUp
			{
			  public:
				/// @brief Globally allow pull-up resistors (default on reset)
				void enable() { MCUCR &= ~(1 << PUD); }

				/// @brief Globally disallow pull-up resistors
				void disable() { MCUCR |= (1 << PUD); }
			};

		  public:
			/// @brief Global pull-up resistor control
			PullUp pullup {};
		};

	  public:
		Analog analog {};
		Digital digital {};
		Interrupt interrupt {};
		USI usi {};
		Port port {};

		[[nodiscard]] auto eeprom() { return devuino::device::EEPROM<eeprom_size, EepromBackend> {EepromBackend {}}; }
	};

	using ATtiny25 = ATtinyX5<2048, 128, 128>;
	using ATtiny45 = ATtinyX5<4096, 256, 256>;
	using ATtiny85 = ATtinyX5<8192, 512, 512>;
}