#ifndef ONBOARD_H
#define ONBOARD_H

#include "Pin.h"
#include <Arduino.h>

namespace devuino
{
    namespace pin
    {
        class Onboard : public Pin
        {
          public:
            Onboard(byte pin)
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
                }
            };

            const byte pin;
        };
    }
}

#endif
