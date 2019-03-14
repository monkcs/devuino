#ifndef DELAYSYNC_H
#define DELAYSYNC_H

#include <Arduino.h>

namespace devuino
{
    static void DelaySync(const uint32_t milliseconds)
    {
        delay(milliseconds);
    };
}

#endif
