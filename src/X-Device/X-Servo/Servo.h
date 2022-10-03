#ifndef SERVO_H
#define SERVO_H

#include "../../Output/OutputDigital.h"
#include "../../Rotation/Rotation.h"
#include "../../Delay/DelayAsync.h"
/*
namespace devuino
{
    namespace device
    {
        // Just for test

        template <class T>
            constexpr T map(const T value, const T inputmin, const T inputmax, const T outputmin, const T outputmax)
            {
                return (value - inputmin) * (outputmax - outputmin) / (inputmax - inputmin) + outputmin;
            };


        template <typename T>
            class Servo : public OutputDigital, Rotation
        {
            public:
                Servo(T pin)
                    : pin(pin), timer(DelayAsync(0))
                {
                    this->pin.initiate(pin::Mode::OutputDigital);
                    off();
                }
                ~Servo()
                {
                    off();
                }

                void degree(const double rotate) override
                {
                    rotation = map<double>(rotate, -90.0, 90.0, 0.001, 0.002);
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

                void percent(double rotate) override
                {
                    degree((180.0 * rotate) - 90.0);
                }

                void update()
                {
                    if (active)
                    {

                    }
                }

            protected:
                T pin;
                DelayAsync timer;

                void change(const bool state)
                {
                    active = state;
                }
        };
    }
}*/
#endif
