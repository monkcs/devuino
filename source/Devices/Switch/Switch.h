#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>
#include "OutputDigital.h"

namespace devuino
{
    class Switch : public OutputDigital
    {
      public:
        Switch(byte pin);
        ~Switch();

        void off() override;
        void on() override;

      protected:
        void change(bool state);
        const byte pin;
    };
}

#endif