#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution final
    {
      public:
        Resolution(unsigned int bits);
        
        const unsigned int bits;
        const unsigned int resolution;
    };
}

#endif