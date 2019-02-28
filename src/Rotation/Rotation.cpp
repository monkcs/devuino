#include "Rotation.h"

namespace devuino
{
    void Rotation::radian(double rotate)
    {
        degree(rotate * (180.0 / 3.1415));
    }
}
