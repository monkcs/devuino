#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include "../CharacterDisplay.h"

namespace devuino
{
    class SevenSegmentCharacter final
    {
        public:
            enum class Encoding : uint8_t
            {
                None,
                abcdefg
            };

            explicit constexpr SevenSegmentCharacter(const int character, const Encoding encoding = Encoding::abcdefg)
                : character ((encoding == Encoding::None) ? static_cast<uint8_t>(character) : convert(character, encoding)) { };

            explicit constexpr SevenSegmentCharacter(const char character, const Encoding encoding = Encoding::abcdefg)
                : character(convert(character, encoding)) { };

            constexpr SevenSegmentCharacter()
                : character(0x0) { };

            constexpr explicit operator uint8_t() const { return character; };

      private:
        uint8_t character;

        // TODO This is not an optimal solution
        class Lookup final
        {
          public:
            constexpr const uint8_t operator[] (const unsigned int index) const
            {
                return table[index];
            };

          private:
            const uint8_t table[10] =
            {
                    0x7e, // 0
                    0x30, // 1
                    0x6d, // 2
                    0x79, // 3
                    0x33, // 4
                    0x5b, // 5
                    0x5f, // 6
                    0x70, // 7
                    0x7f, // 8
                    0x7b, // 9
            };
        };

        constexpr uint8_t convert(const int character, const Encoding encoding) const
        {
            return (0 <= character && character < 10) ? lookup(character) : 0x0;
        };


        constexpr uint8_t convert(const char character, const Encoding encoding) const
        {
            return (character >= 32 && character <= 126) ? lookup(character - 48) : 0x0;
        };

        constexpr uint8_t lookup(const int character) const
        {
            return Lookup()[character];
        };
    };

    /* User defined litterals */
    constexpr SevenSegmentCharacter operator""_char7s (const unsigned long long int character)    { return SevenSegmentCharacter { static_cast<int>(character) }; }
    constexpr SevenSegmentCharacter operator""_char7s (const char character)                      { return SevenSegmentCharacter { character }; }




    template <typename TPosition, typename TCharacter>
    class SegmentDisplay : public CharacterDisplay<TPosition, TCharacter>
    {
        public:
            SegmentDisplay(const Vector2D<TPosition> dimension,
                           const Cursor<TCharacter, TPosition> cursor,
                           const Direction direction)
            : CharacterDisplay<TPosition, TCharacter>(dimension, cursor, direction) {}

            //virtual constexpr void print(TCharacter number) = 0;
        protected:
    };
}

#endif
