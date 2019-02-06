#ifndef ASYNC_H
#define ASYNC_H

namespace devuino
{
    namespace delay
    {
        class Async
        {
            public:
                Async(uint32_t milliseconds);

                bool expired();
                void delay(uint32_t milliseconds);

            private:
                uint32_t target;
                uint32_t delaytime;
        };
    }
}

#endif
