#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution
    {
      public:
        Resolution(int bits);
        int bits();
        int resolution();

      private:
        const int bitresolution;
    };
}

#endif