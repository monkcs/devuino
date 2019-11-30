#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include "../CharacterDisplay.h"

namespace devuino
{
    class SevenSegmentCharacter
    {
        public:
            enum class Encoding : uint8_t
            {
                abcdefg,
                gfedcba
            };

            SevenSegmentCharacter(const char character, const Encoding encoding = Encoding::gfedcba)
                : character(convert(character, encoding)) { };

            const uint8_t character;

      private:
        /*uint8_t convert(const double character, const Encoding encoding) const
        {
            switch (character)
            {
                case 0:
                    return (encoding == Encoding::abcdefg) ? 0x7E : 0x3F;
                    break;
                case 1:
                    return (encoding == Encoding::abcdefg) ? 0x30 : 0x06;
                    break;
                case 2:
                    return (encoding == Encoding::abcdefg) ? 0x6D : 0x5B;
                    break;
                case 3:
                    return (encoding == Encoding::abcdefg) ? 0x79 : 0x4F;
                    break;
                case 4:
                    return (encoding == Encoding::abcdefg) ? 0x33 : 0x66;
                    break;
                case 5:
                    return (encoding == Encoding::abcdefg) ? 0x5B : 0x6D;
                    break;
                case 6:
                    return (encoding == Encoding::abcdefg) ? 0x5F : 0x7D;
                    break;
                case 7:
                    return (encoding == Encoding::abcdefg) ? 0x70 : 0x07;
                    break;
                case 8:
                    return (encoding == Encoding::abcdefg) ? 0x7F : 0x7F;
                    break;
                case 9:
                    return (encoding == Encoding::abcdefg) ? 0x7B : 0x6F;
                    break;

                default:
                    return 0x0;
                    break;
            }
        };*/

        uint8_t convert(const char character, const Encoding encoding) const
        {
            switch (character)
            {
                case '0':
                    return (encoding == Encoding::abcdefg) ? 0x7E : 0x3F;
                    break;
                case '1':
                    return (encoding == Encoding::abcdefg) ? 0x30 : 0x06;
                    break;
                case '2':
                    return (encoding == Encoding::abcdefg) ? 0x6D : 0x5B;
                    break;
                case '3':
                    return (encoding == Encoding::abcdefg) ? 0x79 : 0x4F;
                    break;
                case '4':
                    return (encoding == Encoding::abcdefg) ? 0x33 : 0x66;
                    break;
                case '5':
                    return (encoding == Encoding::abcdefg) ? 0x5B : 0x6D;
                    break;
                case '6':
                    return (encoding == Encoding::abcdefg) ? 0x5F : 0x7D;
                    break;
                case '7':
                    return (encoding == Encoding::abcdefg) ? 0x70 : 0x07;
                    break;
                case '8':
                    return (encoding == Encoding::abcdefg) ? 0x7F : 0x7F;
                    break;
                case '9':
                    return (encoding == Encoding::abcdefg) ? 0x7B : 0x6F;
                    break;

                default:
                    return 0x0;
                    break;
            }
        };
    };

    template <typename TPosition, typename TCharacter>
    class SegmentDisplay : public CharacterDisplay<TPosition, TCharacter>
    {
        public:
            SegmentDisplay(const Vector2D<TPosition> dimension,
                           const Cursor<TCharacter, TPosition> cursor,
                           const Direction direction)
            : CharacterDisplay<TPosition, TCharacter>(dimension, cursor, direction) {}

        private:
            void print(TCharacter number) const
            {
                //while (number > 0)
                {
                    //const T digit = number % 10;
                    //number /= 10;
                    //print digit
                }
            }
    };
}

#endif
