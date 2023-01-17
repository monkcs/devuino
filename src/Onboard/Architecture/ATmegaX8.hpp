#pragma once

#include "../../Device/EEPROM/EEPROM.hpp"
#include "../Analog.hpp"
#include "../Digital.hpp"
#include "../EepromBackend:tiny:mega.hpp"
#include "../SPI:mega.hpp"

#include <Arduino.h>

namespace devuino::onboard
{
	enum class InterruptExternal
	{
		Interrupt0,
		Interrupt1
	};

	enum class Trigger : uint8_t
	{
		Low = 0,
		Change = 1,
		FallingEdge = 2,
		RisingEdge = 3
	};

	enum class PinChangeChannel
	{
		All,

		/// @brief Same as Pin_0_1_2_3_4_5_6_7
		Channel0,
		/// @brief Same as Channel0
		Pin_0_1_2_3_4_5_6_7,

		/// @brief Same as Pin_8_9_10_11_12_13_14
		Channel1,
		/// @brief Same as Channel1
		Pin_8_9_10_11_12_13_14,

		/// @brief Same as Pin_16_17_18_19_20_21_22_23
		Channel2,
		/// @brief Same as Channel2
		Pin_16_17_18_19_20_21_22_23
	};

	template<unsigned int flash_size, int eeprom_size, int sram_size>
	class ATmegaX8
	{
		class Analog
		{
		  public:
			/// Low-level access to analog output pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto output(const int pin) { return AnalogOutput {pin}; }

			/// Low-level access to analog input pin onboard device.
			/// @param pin Arduino analog pin numbering.
			[[nodiscard]] auto input(const int pin)
			{
				switch (pin)
				{
					case A1: return AnalogInput {pin, PC1, DDRC};
					case A2: return AnalogInput {pin, PC2, DDRC};
					case A3: return AnalogInput {pin, PC3, DDRC};
					case A4: return AnalogInput {pin, PC4, DDRC};
					case A5: return AnalogInput {pin, PC5, DDRC};

					case A0:
					default: return AnalogInput {pin, PC0, DDRC};
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
					case 1: return DigitalOutput {PD1, PORTD, DDRD};
					case 2: return DigitalOutput {PD2, PORTD, DDRD};
					case 3: return DigitalOutput {PD3, PORTD, DDRD};
					case 4: return DigitalOutput {PD4, PORTD, DDRD};
					case 5: return DigitalOutput {PD5, PORTD, DDRD};
					case 6: return DigitalOutput {PD6, PORTD, DDRD};
					case 7: return DigitalOutput {PD7, PORTD, DDRD};
					case 8: return DigitalOutput {PB0, PORTB, DDRB};
					case 9: return DigitalOutput {PB1, PORTB, DDRB};
					case 10: return DigitalOutput {PB2, PORTB, DDRB};
					case 11: return DigitalOutput {PB3, PORTB, DDRB};
					case 12: return DigitalOutput {PB4, PORTB, DDRB};
					case 13: return DigitalOutput {PB5, PORTB, DDRB};
					case 14: return DigitalOutput {PC0, PORTC, DDRC};
					case 15: return DigitalOutput {PC1, PORTC, DDRC};
					case 16: return DigitalOutput {PC2, PORTC, DDRC};
					case 17: return DigitalOutput {PC3, PORTC, DDRC};
					case 18: return DigitalOutput {PC4, PORTC, DDRC};
					case 19: return DigitalOutput {PC5, PORTC, DDRC};
					case 20: return DigitalOutput {PB6, PORTB, DDRB};
					case 21: return DigitalOutput {PB7, PORTB, DDRB};
					case 22: return DigitalOutput {PC6, PORTC, DDRC};

					case 0:
					default: return DigitalOutput {PD0, PORTD, DDRD};
				}
			}

			/// Low-level access to digital input pin onboard device.
			/// @param pin Arduino pin numbering.
			[[nodiscard]] auto input(const int pin)
			{
				switch (pin)
				{
					case 1: return DigitalInput {PD1, PORTD, PIND, DDRD};
					case 2: return DigitalInput {PD2, PORTD, PIND, DDRD};
					case 3: return DigitalInput {PD3, PORTD, PIND, DDRD};
					case 4: return DigitalInput {PD4, PORTD, PIND, DDRD};
					case 5: return DigitalInput {PD5, PORTD, PIND, DDRD};
					case 6: return DigitalInput {PD6, PORTD, PIND, DDRD};
					case 7: return DigitalInput {PD7, PORTD, PIND, DDRD};
					case 8: return DigitalInput {PB0, PORTB, PINB, DDRB};
					case 9: return DigitalInput {PB1, PORTB, PINB, DDRB};
					case 10: return DigitalInput {PB2, PORTB, PINB, DDRB};
					case 11: return DigitalInput {PB3, PORTB, PINB, DDRB};
					case 12: return DigitalInput {PB4, PORTB, PINB, DDRB};
					case 13: return DigitalInput {PB5, PORTB, PINB, DDRB};
					case 14: return DigitalInput {PC0, PORTC, PINC, DDRC};
					case 15: return DigitalInput {PC1, PORTC, PINC, DDRC};
					case 16: return DigitalInput {PC2, PORTC, PINC, DDRC};
					case 17: return DigitalInput {PC3, PORTC, PINC, DDRC};
					case 18: return DigitalInput {PC4, PORTC, PINC, DDRC};
					case 19: return DigitalInput {PC5, PORTC, PINC, DDRC};
					case 20: return DigitalInput {PB6, PORTB, PINB, DDRB};
					case 21: return DigitalInput {PB7, PORTB, PINB, DDRB};
					case 22: return DigitalInput {PC6, PORTC, PINC, DDRC};

					case 0:
					default: return DigitalInput {PD0, PORTD, PIND, DDRD};
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
				/// @brief Access to pin change interrupt
				/// @param interrupt Pin change using PCINTx numbering
				[[nodiscard]] constexpr PinChangePin pin(const int interrupt)
				{
					switch (interrupt)
					{
						case 1: return PinChangePin {PCMSK0, PCINT1};
						case 2: return PinChangePin {PCMSK0, PCINT2};
						case 3: return PinChangePin {PCMSK0, PCINT3};
						case 4: return PinChangePin {PCMSK0, PCINT4};
						case 5: return PinChangePin {PCMSK0, PCINT5};
						case 6: return PinChangePin {PCMSK0, PCINT6};
						case 7: return PinChangePin {PCMSK0, PCINT7};

						case 8: return PinChangePin {PCMSK1, PCINT8};
						case 9: return PinChangePin {PCMSK1, PCINT9};
						case 10: return PinChangePin {PCMSK1, PCINT10};
						case 11: return PinChangePin {PCMSK1, PCINT11};
						case 12: return PinChangePin {PCMSK1, PCINT12};
						case 13: return PinChangePin {PCMSK1, PCINT13};
						case 14: return PinChangePin {PCMSK1, PCINT14};

						case 16: return PinChangePin {PCMSK2, PCINT16};
						case 17: return PinChangePin {PCMSK2, PCINT17};
						case 18: return PinChangePin {PCMSK2, PCINT18};
						case 19: return PinChangePin {PCMSK2, PCINT19};
						case 20: return PinChangePin {PCMSK2, PCINT20};
						case 21: return PinChangePin {PCMSK2, PCINT21};
						case 22: return PinChangePin {PCMSK2, PCINT22};

						case 0:
						default: return PinChangePin {PCMSK0, PCINT0};
					}
				}

				/// @brief Enable interrupt channel for pin change
				/// @param channel Channel to enable
				void enable(const PinChangeChannel channel)
				{
					switch (channel)
					{
						case PinChangeChannel::Channel0:
						case PinChangeChannel::Pin_0_1_2_3_4_5_6_7:
						{
							PCICR |= (1 << PCIE0);
							break;
						}
						case PinChangeChannel::Channel1:
						case PinChangeChannel::Pin_8_9_10_11_12_13_14:
						{
							PCICR |= (1 << PCIE1);
							break;
						}
						case PinChangeChannel::Channel2:
						case PinChangeChannel::Pin_16_17_18_19_20_21_22_23:
						{
							PCICR |= (1 << PCIE2);
							break;
						}

						case PinChangeChannel::All:
						default:
						{
							PCICR |= ((1 << PCIE2) | (1 << PCIE1) | (1 << PCIE0));
							break;
						}
					}
				}

				/// @brief Disable interrupt channel for pin change
				/// @param channel Channel to disable
				void disable(const PinChangeChannel channel)
				{
					switch (channel)
					{
						case PinChangeChannel::Channel0:
						case PinChangeChannel::Pin_0_1_2_3_4_5_6_7:
						{
							PCICR &= ~(1 << PCIE0);
							break;
						}
						case PinChangeChannel::Channel1:
						case PinChangeChannel::Pin_8_9_10_11_12_13_14:
						{
							PCICR &= ~(1 << PCIE1);
							break;
						}
						case PinChangeChannel::Channel2:
						case PinChangeChannel::Pin_16_17_18_19_20_21_22_23:
						{
							PCICR &= ~(1 << PCIE2);
							break;
						}

						case PinChangeChannel::All:
						default:
						{
							PCICR &= ~((1 << PCIE2) | (1 << PCIE1) | (1 << PCIE0));
							break;
						}
					}
				}
			};

			class External
			{
				uint8_t interrupt;
				const int shiftmask;

			  public:
				constexpr External(const uint8_t interrupt) : interrupt {interrupt}, shiftmask {(interrupt == INT0) ? 0 : 2} { }

				/// @brief Attach interrupt
				/// @param trigger Condition that will trigger an interrupt.
				void attach(const Trigger trigger)
				{
					EICRA |= static_cast<uint8_t>(trigger) << shiftmask;
					EIMSK |= (1 << interrupt);
				}

				/// @brief Detach interrupt
				void detach() { EIMSK &= ~(1 << interrupt); }
			};

		  public:
			/// @brief Pin change interrupt
			PinChange pinchange {};

			/// @brief Access to external pin interrupt
			/// @param interrupt 0 for INT0, 1 for INT1
			External external(const int interrupt)
			{
				switch (interrupt)
				{
					case 1: return External {INT1};

					case 0:
					default: return External {INT0};
				}
			}

			/// @brief Enable global interrupts
			void enable() const { sei(); }

			/// @brief Disable global interrupts
			void disable() const { cli(); }
		};

	  public:
		Analog analog {};
		Digital digital {};
		Interrupt interrupt {};

		[[nodiscard]] constexpr auto spi() { return SPImega {}; }

		[[nodiscard]] auto eeprom() { return devuino::device::EEPROM<eeprom_size, EepromBackend> {EepromBackend {}}; }
	};

	using ATmega328 = ATmegaX8<32768, 1024, 2048>;
}