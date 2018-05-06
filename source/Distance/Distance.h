#ifndef DISTANCE_H
#define DISTANCE_H

namespace devuino
{
    class Distance
    {
      public:
        virtual float metre() = 0;
        float decimetre();
        float centimetre();
        float millimetre();
        float micrometre();
        float yard();
        float foot();
        float inch();
    };
}
#endif
