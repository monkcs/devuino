#ifndef ONBOARD_H
#define ONBOARD_H

#include "Pin.h"
#include <Arduino.h>

namespace devuino
{
    namespace pin
    {
        class Onboard final : public Pin
        {
          public:
            constexpr Onboard(const uint8_t pin)
                : pin(pin){};

            int analogread() const override
            {
                return analogRead(pin);
            };

            void analogwrite(const int value) const override
            {
                analogWrite(pin, value);
            };

            bool digitalread() const override
            {
                return digitalRead(pin);
            };

            void digitalwrite(const bool value) const override
            {
                digitalWrite(pin, value);
            };

            void initiate(const devuino::pin::Mode mode, const Resistor pull = Resistor::None) const override
            {
                /* Not possible to use constexpr on this code
                switch (mode)
                {
                    case Mode::InputAnalog:
                    case Mode::InputDigital:
                    {
                        if (pull == Resistor::PullUp)
                        {
                            pinMode(pin, INPUT_PULLUP);
                        }
                        else
                        {
                            pinMode(pin, INPUT);
                        }
                    }
                    break;

                    case Mode::OutputAnalog:
                    case Mode::OutputDigital:
                    {
                        pinMode(pin, OUTPUT);
                        digitalwrite(false);
                    }
                    break;
                }*/

                pinMode(pin, pinmode(mode, pull));
            };

          private:
            constexpr uint8_t pinmode(const devuino::pin::Mode mode, const Resistor pull = Resistor::None)
            {
                return (mode == Mode::InputAnalog || mode == Mode::InputDigital)
                        ? ((pull == Resistor::PullUp) ? (INPUT_PULLUP) : (INPUT))
                        : (OUTPUT);
            };

            const uint8_t pin;
        };
    }
}

#endif
