#ifndef ROTATION_H
#define ROTATION_H

namespace devuino
{
    class Rotation
    {
      public:
        virtual void degree(double rotate) = 0;
        virtual void percent(double rotate) = 0;
        void radian(double rotate);

      protected:
        double rotation;
    };
}
#endif
