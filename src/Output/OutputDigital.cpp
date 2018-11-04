#include "OutputDigital.h"

namespace devuino
{
    void OutputDigital::set(bool value)
    {
        if (value)
        {
            on();
        }
        else
        {
            off();
        }
    }
    
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