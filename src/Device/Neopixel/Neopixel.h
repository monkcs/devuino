#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "../../Light/Colour.h"
#include "../../Light/Light.h"
#include "../../Output/OutputDigital.h"
#include "../../Pin/Onboard.h"
#include "WS2812.h"

#include <Arduino.h>

namespace devuino
{
	namespace device
	{
		template<class Device, size_t N, bool Individual = true>
		class Neopixel : public Light, public OutputDigital
		{
			static_assert(N > 0, "Number of pixels cannot be zero");

		  public:
			Neopixel(/*const pin::Onboard pin, */ const Colour colour = {0, 0, 0}, const bool initial = false) : Light {Resolution(8)}, OutputDigital {initial}
			//,pin(pin)
			{
				for (auto& pixel : pixels)
				{
					pixel = colour;
				}

				DDRD |= (1u << 2);
				update();
			}

			~Neopixel()
			{
				off();
			}

			void operator=(const bool value)
			{
				status = value;
				set(value);
			};
			void operator=(const bool value) const
			{
				set(value);
			};

			unsigned int brightness() const
			{
				return bright;
			}

			void brightness(const unsigned int value)
			{
				bright = value;
				set(status);
			}

			constexpr Colour operator[](const size_t index) const
			{
				return pixels[index];
			};

			Colour& operator[](const size_t index)
			{
				return pixels[index];
			};

			devuino::tools::Iterator<const Colour> begin() const
			{
				return {pixels};
			}

			devuino::tools::Iterator<const Colour> end() const
			{
				return {pixels + N};
			}

			devuino::tools::Iterator<Colour> begin()
			{
				return {pixels};
			}

			devuino::tools::Iterator<Colour> end()
			{
				return {pixels + N};
			}

			void update() const
			{
				cli();

				if (status)
				{
					if (bright == bitsize.maximum)
					{
						if (Individual)
						{
							for (const auto& pixel : pixels)
							{
								send(pixel.green);
								send(pixel.red);
								send(pixel.blue);
							}
						}
						else
						{
							for (size_t counter = 0; counter < N; counter++)
							{
								send(pixels[0].green);
								send(pixels[0].red);
								send(pixels[0].blue);
							}
						}
					}
					else
					{
						const double fraction = static_cast<double>(bright) / static_cast<double>(bitsize.maximum);
						if (Individual)
						{
							for (const auto& pixel : pixels)
							{
								send(static_cast<uint8_t>(pixel.green * fraction));
								send(static_cast<uint8_t>(pixel.red * fraction));
								send(static_cast<uint8_t>(pixel.blue * fraction));
							}
						}
						else
						{
							for (size_t counter = 0; counter < N; counter++)
							{
								send(static_cast<uint8_t>(pixels[0].green * fraction));
								send(static_cast<uint8_t>(pixels[0].red * fraction));
								send(static_cast<uint8_t>(pixels[0].blue * fraction));
							}
						}
					}
				}
				else
				{
					/* Turn leds off */
					for (size_t counter = 0; counter < (N * 3); counter++)
					{
						send(0);
					}
				}

				sei();

				/* The leds will latch after a delay */
				_delay_us(600);
			};

		  protected:
			// const pin::Onboard pin;
			Colour pixels[(Individual ? N : 1)];

			void set(const bool value) const override
			{
				update();
			}

			void send(uint8_t data) const
			{
				auto write = [this](const bool value) {
					if (value)
					{
						asm volatile("sbi %[port], %[bit] \n\t"
									 ".rept %[on]         \n\t"
									 "nop                 \n\t"
									 ".endr               \n\t"
									 "cbi %[port], %[bit] \n\t"
									 ".rept %[off]        \n\t"
									 "nop                 \n\t"
									 ".endr               \n\t" ::[port] "I"(_SFR_IO_ADDR(PORTD)),
									 [ bit ] "I"(2), [ on ] "I"(nop(Device::one::high) - 2), [ off ] "I"(nop(Device::one::low) - 2));
					}
					else
					{
						asm volatile("sbi %[port], %[bit] \n\t"
									 ".rept %[on]         \n\t"
									 "nop                 \n\t"
									 ".endr               \n\t"
									 "cbi %[port], %[bit] \n\t"
									 ".rept %[off]        \n\t"
									 "nop                 \n\t"
									 ".endr               \n\t" ::[port] "I"(_SFR_IO_ADDR(PORTD)),
									 [ bit ] "I"(2), [ on ] "I"(nop(Device::zero::high) - 2), [ off ] "I"(nop(Device::zero::low) - 2));
					}
				};

				for (uint8_t bit = 0; bit < 8; bit++)
				{
					/* Send bits in MSB order */
					write((data >> 7) & 1);
					data <<= 1;
				}
			};

			/* Calculates the number off nop instructions to run as a delay */
			constexpr unsigned int nop(const unsigned int nanoseconds) const
			{
				return (nanoseconds / (1000000000ul / F_CPU));
			};
		};
	}
}
#endif
