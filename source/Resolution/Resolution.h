#ifndef RESOLUTION_H
#define RESOLUTION_H

namespace devuino
{
    class Resolution
    {
      protected:
        int resolution();
        void resolution(byte bits);

      private:
        byte bitresolution = 8;
    };
}

#endif