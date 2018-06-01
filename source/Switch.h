#ifndef SWITCH_H
#define SWITCH_H

#include "OutputDigital.h"

namespace devuino
{
    class Switch : public OutputDigital
    {
      public:
        Switch(int pin);
        ~Switch();

        void off() override;
        void on() override;

      protected:
        void change(bool state);
        int pin;
    };
}

#endif