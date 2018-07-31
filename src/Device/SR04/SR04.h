#ifndef SR04_H
#define SR04_H

#include "Distance.h"

namespace devuino
{
    namespace device
    {
        template <typename T>
        class SR04 : public Distance
        {
          public:
            SR04(T input, T output, float minimum = 0.02, float maximum = 4.0);
            float metre() override;

          private:
            const float minimum;
            const float maximum;
            T input;
            T output;
        };
    }
}

#endif