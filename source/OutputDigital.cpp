#include "OutputDigital.h"

namespace devuino
{
    void OutputDigital::toggle()
    {
        if ((active = !active))
        {
            on();
        }
        else
        {
            off();
        }
    }
}