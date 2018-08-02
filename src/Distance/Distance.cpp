#include "Distance.h"

namespace devuino
{
    float Distance::distance(Imperial unit)
    {
        switch (unit)
        {
            case Imperial::Nautical:
                return distance() / 1852.0;
                break;
            case Imperial::Mile:
                return distance() / 1609.344;
                break;
            case Imperial::Furlong:
                return distance() / 201.168;
                break;
            case Imperial::Chain:
                return distance() / 20.1168;
                break;
            case Imperial::Yard:
                return distance() / 0.9144;
                break;
            case Imperial::Foot:
                return distance() / 0.3048;
                break;
            case Imperial::Inch:
                return distance() / 0.0254;
                break;
            case Imperial::Thou:
                return distance() / 0.0000254;
                break;

            default:
                return distance();
        }
    }

    float Distance::distance(SI unit)
    {

        switch (unit)
        {
            case SI::Giga:
                return distance() / 1000000000.0;
                break;
            case SI::Mega:
                return distance() / 1000000.0;
                break;
            case SI::Kilo:
                return distance() / 1000.0;
                break;
            case SI::Hekto:
                return distance() / 100.0;
                break;
            case SI::Deka:
                return distance() / 10.0;
                break;
            case SI::Metre:
                return distance();
                break;
            case SI::Deci:
                return distance() * 10.0;
                break;
            case SI::Centi:
                return distance() * 100.0;
                break;
            case SI::Milli:
                return distance() * 1000.0;
                break;
            case SI::Micro:
                return distance() * 1000000.0;
                break;
            case SI::Nano:
                return distance() * 1000000000.0;
                break;

            default:
                return distance();
        }
    }
}