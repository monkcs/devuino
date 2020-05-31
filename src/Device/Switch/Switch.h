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
            Switch(const T pin) : pin(pin)
            {
                this->pin.initiate(pin::Mode::OutputDigital);
                off();
            }
            ~Switch()
            {
                off();
            }

            void operator= (const bool value) const
            {
                set(value);
            }

          protected:
            const T pin;
            bool value;

            void set(const bool value) override
            {
                pin.digitalwrite(value);
                this->value = value;
            };

            bool status() const override
            {
                return value;
            };
        };
    }
}
#endif
