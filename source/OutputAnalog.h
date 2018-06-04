#ifndef OUTPUTANALOG_H
#define OUTPUTANALOG_H

#include "OutputDigital.h"
#include "Resolution.h"

namespace devuino
{
    class OutputAnalog : public OutputDigital
    {
      public:
        OutputAnalog(int bitresolution);
        virtual void analog(int value) = 0;

      protected:
        Resolution bitsize;
    };
}

#endif