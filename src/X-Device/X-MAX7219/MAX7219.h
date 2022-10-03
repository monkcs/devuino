/*
 * Datasheet (https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 * Archive (https://web.archive.org/https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 */

#pragma once

#include "../..//Display/Direction.h"
#include "../../Display/CharacterDisplay/SegmentDisplay/SegmentDisplay.h"
#include "../../Interface/SPI.h"
#include "../../Light/Light.h"
#include "../../Output/OutputDigital.h"

namespace devuino
{
	namespace device
	{
		template<typename Type>
		class MAX7219 final : public OutputDigital, public Light, public SegmentDisplay<uint8_t, SevenSegmentCharacter>
		{
		  public:
			enum class Decode : uint8_t
			{
				None = 0x0,
				D0 = 0x1,
				D0123 = 0x0f,
				D01234567 = 0xff
			};

			MAX7219(const devuino::interface::spi::Controller<Type> spi) :
				OutputDigital(true),
				Light(Resolution {4}),
				SegmentDisplay<uint8_t, SevenSegmentCharacter>(
					Vector2D<uint8_t>(8, 1),
					Cursor<SevenSegmentCharacter, uint8_t>(SevenSegmentCharacter('_'), false, Vector2D<uint8_t>(0, 0)),
					Direction(Direction::Horizontal::Left, Direction::Vertical::None, Direction::Primary::Horizontal)),
				spi(spi)
			{
				this->spi.initiate();

				// Reset display
				brightness(bitsize.maximum);
				decode(Decode::None);
				clear();
				scanlimit(dimension.x);
				test(false);
				on();
			};
			~MAX7219() { off(); };

			/* Turn on or off the display to enter low-power mode.
			It is still possible to program the display in power-off mode. */
			void operator=(const bool value) const { set(value); };

			SevenSegmentCharacter backend[8] = {};

			SevenSegmentCharacter& operator[](const uint8_t index)
			{
				const auto guard = (index < 9) ? index : 0;
				return backend[guard];
			};

			constexpr SevenSegmentCharacter operator[](const uint8_t index) const
			{
				const auto guard = (index < 9) ? index : 0;
				return backend[guard];
			};

			void print(const SevenSegmentCharacter number)	  // override
			{
				if (cursor.x < dimension.x)
				{
					backend[cursor.x] = number;
					move();
					push();
				}
			};

			void push()
			{
				for (uint8_t index = 0; index < dimension.x; index++)
				{
					const auto digit = (dimension.x - 1) - index;
					spi.transfer(index + 1, static_cast<uint8_t>(backend[digit]));
				}
			};

			constexpr uint8_t count(const unsigned long int number) const { return ((number == 0) ? 0 : (1 + count(number / 10))); };

			constexpr unsigned int absolute(int number) const { return (number < 0) ? -number : number; };

			void print(const long int number)
			{
				auto sign = [=]()
				{
					if (number < 0)
					{
						print(SevenSegmentCharacter('-'));
					}
				};

				auto send = [this](unsigned int number)
				{
					do
					{
						print(SevenSegmentCharacter(static_cast<int>(number % 10)));
						number /= 10;

					} while (number > 0);
				};

				const auto positive = absolute(number);

				if (direction.x == Direction::Horizontal::Right)
				{
					send(positive);
					sign();
				}
				else if (direction.x == Direction::Horizontal::Left)
				{
					sign();

					// Special case for zero.
					const auto offset = (positive == 0) ? 0 : (count(positive) - 1);
					move(offset);

					// Change direction to print digits in right order.
					direction.x = Direction::Horizontal::Right;

					send(positive);

					// Change direction back.
					direction.x = Direction::Horizontal::Left;
					move(offset + 2);
				}

				/* Not used cases
				else if (direction.x == Direction::Horizontal::Center)
				{

				}
				else if (direction.x == Direction::Horizontal::None)
				{

				}
				*/
				push();
			};
		};
	}
}
