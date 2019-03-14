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
            DelayAsync(const uint32_t milliseconds);

            void delay(const uint32_t milliseconds);
            bool reached();

        private:
            uint32_t target;
            uint32_t delaytime;
    };
}
#endif
