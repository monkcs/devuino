#include "Rotation.h"

namespace devuino
{
    void Rotation::radian(float rotate)
    {
        degree(rotate * (180 / 3.1415));
    }
}