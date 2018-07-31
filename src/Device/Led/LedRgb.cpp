#include "LedRgb.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        LedRgb<T>::LedRgb(T redpin, T greenpin, T bluepin)
        {
            pins[0] = redpin;
            pins[1] = greenpin;
            pins[2] = bluepin;

            for (auto pin : pins)
            {
                pin.initiate(pin::Mode::OutputAnalog);
            }
        }

        template <typename T>
        LedRgb<T>::~LedRgb()
        {
            off();
        }

        template <typename T>
        void LedRgb<T>::off()
        {
            brightness(0);
        }

        template <typename T>
        void LedRgb<T>::on()
        {
            brightness(255);
        }

        template <typename T>
        void LedRgb<T>::red(byte value)
        {
            change(pins[0], value);
        }

        template <typename T>
        void LedRgb<T>::green(byte value)
        {
            change(pins[1], value);
        }

        template <typename T>
        void LedRgb<T>::blue(byte value)
        {
            change(pins[2], value);
        }

        template <typename T>
        void LedRgb<T>::change(T pin, byte value)
        {
            pin.analogwrite((byte)(value * (bright / 255)));
        }
    }
}