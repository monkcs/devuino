/*
 * Datasheet (https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 * Archive (https://web.archive.org/https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
 */

#ifndef MAX7219_H
#define MAX7219_H

#include "../../Output/OutputDigital.h"
#include "../../Light/Light.h"
#include "../../Interface/SPI.h"
#include "../../Display/CharacterDisplay/SegmentDisplay/SegmentDisplay.h"
#include "../..//Display/Direction.h"


namespace devuino
{
    namespace device
    {
        template <typename T>
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

            MAX7219(const devuino::interface::spi::Master<T> spi) :
            Light(4),
            spi(spi),
            SegmentDisplay<uint8_t, SevenSegmentCharacter>
            (
                Vector2D<uint8_t>(8, 1),
                Cursor<SevenSegmentCharacter, uint8_t>
                (
                    SevenSegmentCharacter('_'),
                    false,
                    Vector2D<uint8_t>(0, 0)
                ),
                Direction(Direction::Horizontal::Left, Direction::Vertical::None, Direction::Primary::Horizontal)
            )
            {
                this->spi.initiate();

                // Reset display
                brightness(bitsize.maximum());
                decode(Decode::None);
                clear();
                scanlimit(dimension.x);
                test(false);
                on();

            };
            ~MAX7219()
            {
                off();
            };

            /* Turn on or off the display to enter low-power mode.
            It is still possible to program the display in power-off mode. */
            void operator= (const bool value) const
            {
                set(value);
            };

            unsigned int brightness() override
            {
                return bright;
            };

            /* Set brightness from 0 to the bitsize.maximum() */
            void brightness(const unsigned int value) override
            {
                bright = value;
                spi.transfer(0x0a, static_cast<uint8_t>(value));
            }

            /* Set all digits to clear */
            void clear() override
            {
                // TODO This will only clear the display if set to decode to code-b
                for (auto& digit : backend)
                {
                    digit = SevenSegmentCharacter {};
                }
                push();
            }

            /* Set how many of the digits to decode using code-b */
            void decode(const Decode mode) const
            {
                spi.transfer(0x09, static_cast<uint8_t>(mode));
            }

            /* Set how many digit to display from memory. */
            void scanlimit(const uint8_t limit) const
            {
                spi.transfer(0x0b, limit - 1);
            }

            /* Test mode turns on all digits at full brightness.
               All programming is preserved while using this mode. */
            void test(const bool value) const
            {
                spi.transfer(0x0f, value);
            }





            SevenSegmentCharacter backend[8] = {};

            SevenSegmentCharacter& operator[] (const uint8_t index)
            {
                const auto guard = (index < 9) ? index : 0;
                return backend[guard];
            };

            constexpr SevenSegmentCharacter operator[] (const uint8_t index) const
            {
                const auto guard = (index < 9) ? index : 0;
                return backend[guard];
            };

            void print(const SevenSegmentCharacter number) //override
            {
                if (cursor.x < dimension.x)
                {
                    backend[cursor.x] = number;
                    move();
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



            constexpr uint8_t count(const unsigned long int number) const
            {
                return ((number == 0) ? 0 : (1 + count(number / 10)));
            };

            constexpr unsigned int absolute(int number) const
            {
                return (number < 0) ? -number : number;
            };

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


          protected:
            bool active;
            const devuino::interface::spi::Master<T> spi;

            /* Turn on or off the display to enter low-power mode.
            It is still possible to program the display in power-off mode. */
            void set(const bool value) override
            {
                spi.transfer(0x0c, value);
                active = value;
            }

            bool status() const override
            {
                return active;
            };
        };
    }
}

#endif
