#include "Switch.h"
#include "Pin.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        Switch<T>::Switch(T pin)
            : pin(pin)
        {
            this->pin.initiate(pin::Mode::OutputDigital);
            off();
        }

        template <typename T>
        Switch<T>::~Switch()
        {
            off();
        }

        template <typename T>
        void Switch<T>::off()
        {
            change(false);
        }

        template <typename T>
        void Switch<T>::on()
        {
            change(true);
        }

        template <typename T>
        void Switch<T>::change(bool state)
        {
            active = state;
            pin.digitalwrite(state);
        }
    }
}