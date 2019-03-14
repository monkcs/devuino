#ifndef DISTANCE_H
#define DISTANCE_H

namespace devuino
{
    class Distance
    {
        public:
            enum class Imperial
            {
                Nautical,
                Mile,
                Furlong,
                Chain,
                Yard,
                Foot,
                Inch,
                Thou
            };

            enum class SI
            {
                Giga,
                Mega,
                Kilo,
                Hekto,
                Deka,
                Metre,
                Deci,
                Centi,
                Milli,
                Micro,
                Nano
            };

            double distance(const Imperial unit) const
            {
                switch (unit)
                {
                    case Imperial::Nautical:
                        return metre() / 1852.0;
                        break;
                    case Imperial::Mile:
                        return metre() / 1609.344;
                        break;
                    case Imperial::Furlong:
                        return metre() / 201.168;
                        break;
                    case Imperial::Chain:
                        return metre() / 20.1168;
                        break;
                    case Imperial::Yard:
                        return metre() / 0.9144;
                        break;
                    case Imperial::Foot:
                        return metre() / 0.3048;
                        break;
                    case Imperial::Inch:
                        return metre() / 0.0254;
                        break;
                    case Imperial::Thou:
                        return metre() / 0.0000254;
                        break;

                    default:
                        return metre();
                }
            };

            double distance(const SI unit) const
            {
                switch (unit)
                {
                    case SI::Giga:
                        return metre() / 1000000000.0;
                        break;
                    case SI::Mega:
                        return metre() / 1000000.0;
                        break;
                    case SI::Kilo:
                        return metre() / 1000.0;
                        break;
                    case SI::Hekto:
                        return metre() / 100.0;
                        break;
                    case SI::Deka:
                        return metre() / 10.0;
                        break;
                    case SI::Metre:
                        return metre();
                        break;
                    case SI::Deci:
                        return metre() * 10.0;
                        break;
                    case SI::Centi:
                        return metre() * 100.0;
                        break;
                    case SI::Milli:
                        return metre() * 1000.0;
                        break;
                    case SI::Micro:
                        return metre() * 1000000.0;
                        break;
                    case SI::Nano:
                        return metre() * 1000000000.0;
                        break;

                    default:
                        return metre();
                }
            };

            virtual double metre() = 0;
    };
}
#endif
