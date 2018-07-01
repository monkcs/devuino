#ifndef PIN_H
#define PIN_H

namespace devuino::pin
{
    enum class Mode
    {
        InputAnalog,
        InputDigital,
        OutputAnalog,
        OutputDigital

    };

    enum class Resistor
    {
        PullUp,
        PullDown,
        None
    };

    class Pin
    {
      public:
        virtual int analogread() = 0;
        virtual void analogwrite(int value) = 0;
        virtual bool digitalread() = 0;
        virtual void digitalwrite(bool value) = 0;
        virtual void initiate(devuino::pin::Mode mode, Resistor pull = Resistor::None) = 0;
    };
}

#endif