#ifndef ROTATION_H
#define ROTATION_H

namespace devuino
{
    class Rotation
    {
      public:
        virtual void degree(const double rotate) = 0;
        virtual void percent(const double rotate) = 0;
        void radian(const double rotate);

      protected:
        double rotation;
    };
}
#endif
