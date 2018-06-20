#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution final
    {
      public:
        Resolution(int bits);
        
        const int bits;
        const int resolution;
    };
}

#endif