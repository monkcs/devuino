#ifndef LED_H
#define LED_H

#include "Light.h"
#include "OutputDigital.h"

namespace devuino
{
    class Led : public OutputDigital, public Light
    {
      public:
        Led(int pin, int bitresolution = 8);
        ~Led();

        void brightness(int value) override;
        void off() override;
        void on() override;

      protected:
        int pin;
    };
}

#endif