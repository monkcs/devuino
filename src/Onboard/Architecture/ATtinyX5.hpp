#pragma once

#include "../Analog.hpp"
#include "../Digital.hpp"

#include <Arduino.h>

namespace devuino::onboard
{
	class ATtiny25
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
			[[nodiscard]] auto output(const ArduinoPin pin) const { return AnalogOutput {pin}; }

			/// Low-level access to analog input pin onboard device.
			/// @param pin Arduino analog pin numbering.
			[[nodiscard]] auto input(const ArduinoPin pin) const
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
			[[nodiscard]] auto output(const ArduinoPin pin) const
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
			[[nodiscard]] auto input(const ArduinoPin pin) const
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
				void enable() const { GIMSK |= (1 << PCIE); }

				/// Disable interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5),
				/// (whole PORTB).
				void disable() const { GIMSK &= ~(1 << PCIE); }

				/// Attach pin for interrupt on pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4,
				/// 5), (whole PORTB).
				/// @param pin Arduino pin numbering.
				void attach(const ArduinoPin pin) const { PCMSK |= pin; }

				/// Detach pin for interrupt on pin change.
				/// @param pin Arduino pin numbering.
				void detach(const ArduinoPin pin) const { PCMSK &= ~pin; }
			};

			class External
			{
			  public:
				/// Enable interrupt INT0, located on physical pin 7.
				/// @param trigger Condition that will trigger an interrupt.
				void enable(const Trigger trigger) const
				{
					MCUCR |= static_cast<uint8_t>(trigger);
					GIMSK |= (1 << INT0);
				}

				/// Disable interrupt INT0, located on physical pin 7.
				void disable() const { GIMSK &= ~(1 << INT0); }
			};

		  public:
			/// Interrupt for pin change, located on (physical pin 1, 2, 3, 5, 6, 7), (arduino pin 0, 1, 2, 3, 4, 5), (whole PORTB).
			const PinChange pinchange {};

			/// Interrupt INT0, located on physical pin 7.
			const External external {};

			/// Enable global interrupts
			void enable() const { sei(); }

			/// Disable global interrupts
			void disable() const { cli(); }
		};

	  public:
		const Analog analog {};
		const Digital digital {};
		const Interrupt interrupt {};
	};

	using ATtiny45 = ATtiny25;
	using ATtiny85 = ATtiny25;
}