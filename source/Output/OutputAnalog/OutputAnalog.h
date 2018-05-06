#ifndef OUTPUTANALOG_H
#define OUTPUTANALOG_H

#include "../OutputDigital.h"
#include "../../Resolution/Resolution.h"

namespace devuino
{
    class OutputAnalog : public OutputDigital, public Resolution
    {
      public:
        virtual void analog(int value) = 0;
    };
}

#endif