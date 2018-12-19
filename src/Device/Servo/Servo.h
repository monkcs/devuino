#ifndef SERVO_H
#define SERVO_H

#include "../../Output/OutputDigital.h"
#include "../../Rotation/Rotation.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class Servo : public OutputDigital, Rotation
        {
          public:
            Servo(T pin)
                : pin(pin)
            {
                this->pin.initiate(pin::Mode::OutputDigital);
                off();
            }
            ~Servo()
            {
                off();
            }

            void change(bool state)
            {
                active = state;
            }

            void degree(float rotate) override
            {
                // Floor tal och sen map()
                // rotation = map();
            }

            void off() override
            {
                change(false);
            }

            void on() override
            {
                change(true);
            }

            void percent(float rotate) override {
                degree((180.0 * rotate) - 90.0);
            }

            void update()
            {
                if (active)
                {
                    // Mät om tillräckligt med tid har passerat, i så fall stäng av eller på
                }
                else
                {
                    pin.digitalwrite(false);
                }
            }

          protected:
            T pin;
            int time = 0;
        };
    }
}
#endif