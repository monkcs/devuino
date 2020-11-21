#ifndef OUTPUTANALOG_H
#define OUTPUTANALOG_H

#include "../Resolution/Resolution.h"
#include "OutputDigital.h"

namespace devuino
{
    class OutputAnalog : public OutputDigital
    {
      public:
        OutputAnalog(const Resolution bitresolution, const bool initial)
            : OutputDigital{initial}, bitsize{bitresolution} {};

        virtual void analog(const int value) = 0;

      protected:
        const Resolution bitsize;
    };
}

#endif
