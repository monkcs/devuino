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

            int analogread() override
            {
                return analogRead(pin);
            };
            void analogwrite(int value) override
            {
                analogWrite(pin, value);
            };
            bool digitalread() override
            {
                return digitalRead(pin);
            };
            void digitalwrite(bool value) override
            {
                digitalWrite(pin, value);
            };
            void initiate(devuino::pin::Mode mode, Resistor pull = Resistor::None) override
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