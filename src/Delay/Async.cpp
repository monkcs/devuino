#include "Async.h"

namespace devuino
{
    namespace delay
    {
        Async::Async(uint32_t milliseconds) : delaytime(milliseconds)
        {
            /*
               Invoke update function to assign a target value.
               */

            expired();
        }

        void Async::delay(uint32_t milliseconds)
        {
            /*
               Before assigning a new delay, remove the old
               one from "target" to preserve the last time
               assigned from expired(). Then assign the new
               delay.
               */

            target -= delaytime;
            delaytime = milliseconds;
            target += delaytime;
        }

        bool Async::expired()
        {
            const time = millis();

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
}
