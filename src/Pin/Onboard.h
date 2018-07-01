#ifndef ONBOARD_H
#define ONBOARD_H

#include "Pin.h"
#include <Arduino.h>

namespace devuino::pin
{
    class Onboard : public Pin
    {
      public:
        Onboard(byte pin);

        int analogread() override;
        void analogwrite(int value) override;
        bool digitalread() override;
        void digitalwrite(bool value) override;
        void initiate(devuino::pin::Mode mode, Resistor pull = Resistor::None) override;

      protected:
        const byte pin;
    };
}

#endif