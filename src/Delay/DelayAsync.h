#ifndef DELAYASYNC_H
#define DELAYASYNC_H

namespace devuino
{
    class DelayAsync
    {
        /* DelayAsync provice async delay by specifying a delaytime,
           and then polling the reached() method for if the time have
           expired.
           */
        public:
            DelayAsync(const uint32_t milliseconds) : delaytime(milliseconds)
            {
                /*
                Invoke update function to assign a target value.
                */

                reached();
            }

            void delay(const uint32_t milliseconds)
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

            bool reached()
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

        private:
            uint32_t target;
            uint32_t delaytime;
    };
}
#endif
