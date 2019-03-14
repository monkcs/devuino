#ifndef SWITCH_H
#define SWITCH_H

#include "../../Output/OutputDigital.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Switch : public OutputDigital
        {
          public:
            Switch(const T pin)
                : pin(pin)
            {
                this->pin.initiate(pin::Mode::OutputDigital);
                off();
            }
            ~Switch()
            {
                off();
            }

            void off() override
            {
                change(false);
            }
            
            void on() override
            {
                change(true);
            }

          protected:
            T pin;

            void change(const bool state)
            {
                active = state;
                pin.digitalwrite(state);
            }
        };
    }
}
#endif
