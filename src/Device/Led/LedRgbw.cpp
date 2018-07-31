#include "LedRgbw.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        LedRgbw<T>::LedRgbw(T redpin, T greenpin, T bluepin, T whitepin)
        {
            pins[0] = redpin;
            pins[1] = greenpin;
            pins[2] = bluepin;
            pins[3] = whitepin;

            for (auto pin : pins)
            {
                pin.initiate(pin::Mode::OutputAnalog);
            }
        }
        template <typename T>
        LedRgbw<T>::~LedRgbw()
        {
            off();
        }

        template <typename T>
        void LedRgbw<T>::off()
        {
            brightness(0);
        }

        template <typename T>
        void LedRgbw<T>::on()
        {
            brightness(255);
        }

        template <typename T>
        void LedRgbw<T>::red(byte value)
        {
            change(pins[0], value);
        }

        template <typename T>
        void LedRgbw<T>::green(byte value)
        {
            change(pins[1], value);
        }

        template <typename T>
        void LedRgbw<T>::blue(byte value)
        {
            change(pins[2], value);
        }

        template <typename T>
        void LedRgbw<T>::white(byte value)
        {
            change(pins[3], value);
        }

        template <typename T>
        void LedRgbw<T>::change(T pin, byte value)
        {
            pin.analogwrite((byte)(value * (bright / 255)));
        }
    }
}