#ifndef ROTATION_H
#define ROTATION_H

namespace devuino
{
    class Rotation
    {
      public:
        virtual void degree(float rotate) = 0;
        virtual void percent(float rotate) = 0;
        void radian(float rotate);

      protected:
        float rotation;
    };
}
#endif
