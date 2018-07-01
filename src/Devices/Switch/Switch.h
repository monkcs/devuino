#ifndef SWITCH_H
#define SWITCH_H

#include "OutputDigital.h"
#include <Arduino.h>

namespace devuino
{
    template <typename T>
    class Switch : public OutputDigital
    {
      public:
        Switch(T pin);
        ~Switch();

        void off() override;
        void on() override;

      protected:
        void change(bool state);
        T pin;
    };
}

#endif