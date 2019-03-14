#include "DelayAsync.h"
#include <Arduino.h>

namespace devuino
{
    DelayAsync::DelayAsync(const uint32_t milliseconds) : delaytime(milliseconds)
    {
        /*
           Invoke update function to assign a target value.
           */

        reached();
    }

    void DelayAsync::delay(const uint32_t milliseconds)
    {
        /*
           Before assigning a new delay, remove the old
           one from "target" to preserve the last time
           assigned from reached(). Then assign the new
           delay.
           */

        target -= delaytime;
        delaytime = milliseconds;
        target += delaytime;
    }

    bool DelayAsync::reached()
    {
        const auto time = millis();

        if (time <= target)
        {
            return false;
        }
        else
        {
            target = time + delaytime;
            return true;
        }
    }
}
