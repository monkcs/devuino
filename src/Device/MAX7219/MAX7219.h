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

namespace devuino
{
    namespace device
    {
        template <typename T>
        class MAX7219 : public OutputDigital, public Light, public SegmentDisplay<uint8_t, SevenSegmentCharacter>
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
                Direction(Direction::Horizontal::Right, Direction::Vertical::None)
            )
            {
                this->spi.initiate();

                on();
                brightness(bitsize.maximum());
                clear();
                decode(Decode::D01234567);
                scanlimit(7);
                test(false);

                spi.transfer(0x2, 0x3);
                spi.transfer(0x3, 0xf4);

            };
            ~MAX7219()
            {
                off();
            };

            void operator= (const bool value) const
            {
                set(value);
            };

            /* Set brightness from 0 to the bitsize.range.maximum */
            void brightness(const int value) override
            {
                bright = value;
                spi.transfer(0x0a, value);
            }

            /* Set all digits to clear */
            void clear() override
            {
                // TODO This will only clear the display if set to decode to code-b
                for (uint8_t digit = 1; digit < 9; digit++)
                {
                    spi.transfer(digit, 0xf);
                }
            }

            /* Set how many of the digits to decode using code-b */
            void decode(const Decode mode) const
            {
                spi.transfer(0x09, static_cast<uint8_t>(mode));
            }

            /* Turn on display. */
            void on() override
            {
                spi.transfer(0x0c, 0x1);
            }

            /* Turn off the display and enter low-power mode.
               It is still possible to program the display in this mode. */
            void off() override
            {
                spi.transfer(0x0c, 0x0);
            }

            /* Set how many digit to display from memory. */
            void scanlimit(const uint8_t limit) const
            {
                spi.transfer(0x0b, limit);
            }

            /* Test mode turns on all digits at full brightness.
               All programming is preserved while using this mode. */
            void test(const bool value) const
            {
                spi.transfer(0x0f, value ? 0x01 : 0x0);
            }


          protected:
            const devuino::interface::spi::Master<T> spi;
        };
    }
}

#endif
