#ifndef PIN_H
#define PIN_H

namespace devuino
{
    namespace pin
    {
        enum class Mode : uint8_t
        {
            InputAnalog,
            InputDigital,
            OutputAnalog,
            OutputDigital
        };

        enum class Resistor : uint8_t
        {
            PullUp,
            PullDown,
            None
        };

        class Pin
        {
          public:

           /* virtual int analogread() = 0;
            virtual void analogwrite(const int value) = 0;
            virtual bool digitalread() = 0;
            virtual void digitalwrite(const bool value) = 0;*/

            //virtual void initiate(const devuino::pin::Mode mode, const devuino::pin::Resistor pull = Resistor::None) const = 0;
        };
    }
}

#endif
