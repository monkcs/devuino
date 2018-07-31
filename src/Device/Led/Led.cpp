#include "Led.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        Led<T>::Led(T pin, int bitresolution)
            : pin(pin), Light(bitresolution)
        {
            this->pin.initiate(pin::Mode::OutputAnalog);
        }

        template <typename T>
        Led<T>::~Led()
        {
            off();
        }

        template <typename T>
        void Led<T>::brightness(int value)
        {
            bright = value;
            pin.analogwrite(value);
        }

        template <typename T>
        void Led<T>::off()
        {
            brightness(0);
        }

        template <typename T>
        void Led<T>::on()
        {
            brightness(bitsize.resolution - 1);
        }
    }
}