#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution
    {
      public:
        int resolution();
        void resolution(int bits);

      protected:
        int bitresolution = 8;
    };
}

#endif