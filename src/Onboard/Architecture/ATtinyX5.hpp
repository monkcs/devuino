#pragma once

#include "../Analog.hpp"
#include "../Digital.hpp"
#include "../EEPROM.hpp"
#include "../SpiATtiny.hpp"

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
			class ArduinoPin
			{
				uint8_t pin;

			  public:
				constexpr ArduinoPin(const int pin) : pin {static_cast<uint8_t>(pin)} { }
				constexpr operator uint8_t() const { return pin; }
			};

		  public:
			/// Low-level access to analog output pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto output(const ArduinoPin pin) { return AnalogOutput {pin}; }

			/// Low-level access to analog input pin onboard device.
			/// @param pin Arduino analog pin numbering.
			[[nodiscard]] auto input(const ArduinoPin pin)
			{
				switch (pin)
				{
					case A1: return AnalogInput {pin, PB2, DDRB};
					case A2: return AnalogInput {pin, PB4, DDRB};
					case A3: return AnalogInput {pin, PB3, DDRB};

					case A0:
					default: return AnalogInput {pin, PB5, DDRB};
				}
			}
		};

		class Digital
		{
			class ArduinoPin
			{
				int pin;

			  public:
				constexpr ArduinoPin(const int pin) : pin {pin} { }
				constexpr operator int() const { return pin; }
			};

		  public:
			/// Low-level access to digital output pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto output(const ArduinoPin pin)
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
			[[nodiscard]] auto input(const ArduinoPin pin)
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
				class ArduinoPin
				{
					constexpr uint8_t calculate(const int pin) const
					{
						switch (pin)
						{
							case 0: return (1 << PCINT0);
							case 1: return (1 << PCINT1);
							case 2: return (1 << PCINT2);
							case 3: return (1 << PCINT3);
							case 4: return (1 << PCINT4);
							case 5: return (1 << PCINT5);

							default: return 0;
						}
					}

					uint8_t bitmask;

				  public:
					constexpr ArduinoPin(const int pin) : bitmask {calculate(pin)} { }
					constexpr operator uint8_t() const { return bitmask; }
				};

			  public:
				/// Enable interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5),
				/// (whole PORTB).
				void enable() { GIMSK |= (1 << PCIE); }

				/// Disable interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5),
				/// (whole PORTB).
				void disable() { GIMSK &= ~(1 << PCIE); }

				/// Attach pin for interrupt on pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4,
				/// 5), (whole PORTB).
				/// @param pin Arduino pin numbering.
				void attach(const ArduinoPin pin) { PCMSK |= pin; }

				/// Detach pin for interrupt on pin change.
				/// @param pin Arduino pin numbering.
				void detach(const ArduinoPin pin) { PCMSK &= ~pin; }
			};

			class External
			{
			  public:
				/// Enable interrupt INT0, located on physical pin 7.
				/// @param trigger Condition that will trigger an interrupt.
				void enable(const Trigger trigger)
				{
					MCUCR |= static_cast<uint8_t>(trigger);
					GIMSK |= (1 << INT0);
				}

				/// Disable interrupt INT0, located on physical pin 7.
				void disable() { GIMSK &= ~(1 << INT0); }
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

		class USI
		{
		  public:
			USI(const USI&) = delete;
			USI& operator=(const USI&) = delete;

			[[nodiscard]] auto spi() { return SpiATtiny {DDRB, PB2, PB1, PB0}; }
		};

		class EepromBackend
		{
		  public:
			EepromBackend()
			{
				/* Set Programming mode */
				EECR = (0 << EEPM1) | (0 << EEPM0);
			}

			/// @brief Read the value at the current address
			uint8_t read(const uint16_t address) const
			{
				/* Wait for completion of previous write */
				while (EECR & (1 << EEPE)) { }

				if (eeprom_size <= 256)
				{
					EEARL = address;
				}
				else
				{
					EEARH = address >> 8;
					EEARL = address;
				}

				/* Start eeprom read by writing EERE */
				EECR |= (1 << EERE);

				return EEDR;
			}

			void write(const uint16_t address, const uint8_t data)
			{
				/* Wait for completion of previous write */
				while (EECR & (1 << EEPE)) { }

				if (eeprom_size <= 256)
				{
					EEARL = address;
				}
				else
				{
					EEARH = address >> 8;
					EEARL = address;
				}
				EEDR = data;

				/* Write logical one to EEMPE */
				EECR |= (1 << EEMPE);

				/* Start eeprom write by setting EEPE */
				EECR |= (1 << EEPE);
			}
		};

	  public:
		Analog analog {};
		Digital digital {};
		Interrupt interrupt {};
		USI usi {};

		[[nodiscard]] auto eeprom() { return EEPROM<eeprom_size, EepromBackend> {{}}; }
	};

	using ATtiny25 = ATtinyX5<2048, 128, 128>;
	using ATtiny45 = ATtinyX5<4096, 256, 256>;
	using ATtiny85 = ATtinyX5<8192, 512, 512>;
}