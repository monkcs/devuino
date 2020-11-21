#ifndef DISTANCE_H
#define DISTANCE_H

namespace devuino
{
	class Distance
	{
	  public:
		explicit constexpr Distance(const long double metre) : metre(metre)
		{
		}

		// Untill C++20
		// constexpr auto operator<=>(const Distance&) const = default;

		constexpr Distance operator-() const
		{
			return Distance(-this->metre);
		}

		constexpr Distance operator+() const
		{
			return *this;
		}

		Distance& operator+=(Distance const& rhs)
		{
			this->metre += rhs.metre;
			return *this;
		}

		Distance& operator-=(Distance const& rhs)
		{
			this->metre -= rhs.metre;
			return *this;
		}

		Distance& operator*=(Distance const& rhs)
		{
			this->metre *= rhs.metre;
			return *this;
		}

		Distance& operator/=(Distance const& rhs)
		{
			this->metre /= rhs.metre;
			return *this;
		}

		constexpr friend Distance operator+(Distance const& lhs, Distance const& rhs)
		{
			return Distance(lhs.metre + rhs.metre);
		}

		constexpr friend Distance operator-(Distance const& lhs, Distance const& rhs)
		{
			return Distance(lhs.metre - rhs.metre);
		}

		constexpr friend Distance operator*(Distance const& lhs, Distance const& rhs)
		{
			return Distance(lhs.metre * rhs.metre);
		}

		constexpr friend Distance operator/(Distance const& lhs, Distance const& rhs)
		{
			return Distance(lhs.metre / rhs.metre);
		}

		constexpr friend bool operator==(Distance const& lhs, Distance const& rhs)
		{
			return (lhs.metre == rhs.metre);
		}

		constexpr friend bool operator!=(Distance const& lhs, Distance const& rhs)
		{
			return !(lhs == rhs);
		}

		constexpr friend bool operator<(Distance const& lhs, Distance const& rhs)
		{
			return (lhs.metre < rhs.metre);
		}

		constexpr friend bool operator>(Distance const& lhs, Distance const& rhs)
		{
			return rhs < lhs;
		}

		constexpr friend bool operator<=(Distance const& lhs, Distance const& rhs)
		{
			return !(lhs > rhs);
		}

		constexpr friend bool operator>=(Distance const& lhs, Distance const& rhs)
		{
			return !(lhs < rhs);
		}

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

		long double as(const Imperial unit) const
		{
			switch (unit)
			{
				case Imperial::Nautical: return metre / 1852.0;
				case Imperial::Mile: return metre / 1609.344;
				case Imperial::Furlong: return metre / 201.168;
				case Imperial::Chain: return metre / 20.1168;
				case Imperial::Yard: return metre / 0.9144;
				case Imperial::Foot: return metre / 0.3048;
				case Imperial::Inch: return metre / 0.0254;
				case Imperial::Thou: return metre / 0.0000254;
			}
		};

		long double as(const SI unit) const
		{
			switch (unit)
			{
				case SI::Giga: return metre / 1000000000.0;
				case SI::Mega: return metre / 1000000.0;
				case SI::Kilo: return metre / 1000.0;
				case SI::Hekto: return metre / 100.0;
				case SI::Deka: return metre / 10.0;
				case SI::Metre: return metre;
				case SI::Deci: return metre * 10.0;
				case SI::Centi: return metre * 100.0;
				case SI::Milli: return metre * 1000.0;
				case SI::Micro: return metre * 1000000.0;
				case SI::Nano: return metre * 1000000000.0;
			}
		}

	  private:
		long double metre;
	};

	/* User defined litterals */

	constexpr Distance operator""_gigametre(const long double lenght)
	{
		return Distance(lenght * 1000000000.0);
	}
	constexpr Distance operator""_gigametre(const unsigned long long int lenght)
	{
		return Distance(lenght * 1000000000.0);
	}
	constexpr Distance operator""_Gm(const long double lenght)
	{
		return Distance(lenght * 1000000000.0);
	}
	constexpr Distance operator""_Gm(const unsigned long long int lenght)
	{
		return Distance(lenght * 1000000000.0);
	}

	constexpr Distance operator""_megametre(const long double lenght)
	{
		return Distance(lenght * 1000000.0);
	}
	constexpr Distance operator""_megametre(const unsigned long long int lenght)
	{
		return Distance(lenght * 1000000.0);
	}
	constexpr Distance operator""_Mm(const long double lenght)
	{
		return Distance(lenght * 1000000.0);
	}
	constexpr Distance operator""_Mm(const unsigned long long int lenght)
	{
		return Distance(lenght * 1000000.0);
	}

	constexpr Distance operator""_kilometre(const long double lenght)
	{
		return Distance(lenght * 1000.0);
	}
	constexpr Distance operator""_kilometre(const unsigned long long int lenght)
	{
		return Distance(lenght * 1000.0);
	}
	constexpr Distance operator""_km(const long double lenght)
	{
		return Distance(lenght * 1000.0);
	}
	constexpr Distance operator""_km(const unsigned long long int lenght)
	{
		return Distance(lenght * 1000.0);
	}

	constexpr Distance operator""_hektometre(const long double lenght)
	{
		return Distance(lenght * 100.0);
	}
	constexpr Distance operator""_hektometre(const unsigned long long int lenght)
	{
		return Distance(lenght * 100.0);
	}
	constexpr Distance operator""_hm(const long double lenght)
	{
		return Distance(lenght * 100.0);
	}
	constexpr Distance operator""_hm(const unsigned long long int lenght)
	{
		return Distance(lenght * 100.0);
	}

	constexpr Distance operator""_dekametre(const long double lenght)
	{
		return Distance(lenght * 10.0);
	}
	constexpr Distance operator""_dekametre(const unsigned long long int lenght)
	{
		return Distance(lenght * 10.0);
	}
	constexpr Distance operator""_dam(const long double lenght)
	{
		return Distance(lenght * 10.0);
	}
	constexpr Distance operator""_dam(const unsigned long long int lenght)
	{
		return Distance(lenght * 10.0);
	}

	constexpr Distance operator""_metre(const long double lenght)
	{
		return Distance(lenght);
	}
	constexpr Distance operator""_metre(const unsigned long long int lenght)
	{
		return Distance(lenght);
	}
	constexpr Distance operator""_m(const long double lenght)
	{
		return Distance(lenght);
	}
	constexpr Distance operator""_m(const unsigned long long int lenght)
	{
		return Distance(lenght);
	}

	constexpr Distance operator""_decimetre(const long double lenght)
	{
		return Distance(lenght / 10.0);
	}
	constexpr Distance operator""_decimetre(const unsigned long long int lenght)
	{
		return Distance(lenght / 10.0);
	}
	constexpr Distance operator""_dm(const long double lenght)
	{
		return Distance(lenght / 10.0);
	}
	constexpr Distance operator""_dm(const unsigned long long int lenght)
	{
		return Distance(lenght / 10.0);
	}

	constexpr Distance operator""_centimetre(const long double lenght)
	{
		return Distance(lenght / 100.0);
	}
	constexpr Distance operator""_centimetre(const unsigned long long int lenght)
	{
		return Distance(lenght / 100.0);
	}
	constexpr Distance operator""_cm(const long double lenght)
	{
		return Distance(lenght / 100.0);
	}
	constexpr Distance operator""_cm(const unsigned long long int lenght)
	{
		return Distance(lenght / 100.0);
	}

	constexpr Distance operator""_millimetre(const long double lenght)
	{
		return Distance(lenght / 1000.0);
	}
	constexpr Distance operator""_millimetre(const unsigned long long int lenght)
	{
		return Distance(lenght / 1000.0);
	}
	constexpr Distance operator""_mm(const long double lenght)
	{
		return Distance(lenght / 1000.0);
	}
	constexpr Distance operator""_mm(const unsigned long long int lenght)
	{
		return Distance(lenght / 1000.0);
	}

	constexpr Distance operator""_micrometre(const long double lenght)
	{
		return Distance(lenght / 1000000.0);
	}
	constexpr Distance operator""_micrometre(const unsigned long long int lenght)
	{
		return Distance(lenght / 1000000.0);
	}
	constexpr Distance operator""_um(const long double lenght)
	{
		return Distance(lenght / 1000000.0);
	}
	constexpr Distance operator""_um(const unsigned long long int lenght)
	{
		return Distance(lenght / 1000000.0);
	}

	constexpr Distance operator""_nanometre(const long double lenght)
	{
		return Distance(lenght / 1000000000.0);
	}
	constexpr Distance operator""_nanometre(const unsigned long long int lenght)
	{
		return Distance(lenght / 1000000000.0);
	}
	constexpr Distance operator""_nm(const long double lenght)
	{
		return Distance(lenght / 1000000000.0);
	}
	constexpr Distance operator""_nm(const unsigned long long int lenght)
	{
		return Distance(lenght / 1000000000.0);
	}

	constexpr Distance operator""_thou(const long double lenght)
	{
		return Distance(lenght * 0.0000254);
	}
	constexpr Distance operator""_thou(const unsigned long long int lenght)
	{
		return Distance(lenght * 0.0000254);
	}

	constexpr Distance operator""_inch(const long double lenght)
	{
		return Distance(lenght * 0.0254);
	}
	constexpr Distance operator""_inch(const unsigned long long int lenght)
	{
		return Distance(lenght * 0.0254);
	}

	constexpr Distance operator""_foot(const long double lenght)
	{
		return Distance(lenght * 0.3048);
	}
	constexpr Distance operator""_foot(const unsigned long long int lenght)
	{
		return Distance(lenght * 0.3048);
	}

	constexpr Distance operator""_yard(const long double lenght)
	{
		return Distance(lenght * 0.9144);
	}
	constexpr Distance operator""_yard(const unsigned long long int lenght)
	{
		return Distance(lenght * 0.9144);
	}

	constexpr Distance operator""_chain(const long double lenght)
	{
		return Distance(lenght * 20.1168);
	}
	constexpr Distance operator""_chain(const unsigned long long int lenght)
	{
		return Distance(lenght * 20.1168);
	}

	constexpr Distance operator""_furlong(const long double lenght)
	{
		return Distance(lenght * 201.168);
	}
	constexpr Distance operator""_furlong(const unsigned long long int lenght)
	{
		return Distance(lenght * 201.168);
	}

	constexpr Distance operator""_mile(const long double lenght)
	{
		return Distance(lenght * 1609.344);
	}
	constexpr Distance operator""_mile(const unsigned long long int lenght)
	{
		return Distance(lenght * 1609.344);
	}

	constexpr Distance operator""_nautical(const long double lenght)
	{
		return Distance(lenght * 1852.0);
	}
	constexpr Distance operator""_nautical(const unsigned long long int lenght)
	{
		return Distance(lenght * 1852.0);
	}

	class DistanceInput
	{
	  public:
		virtual Distance distance() const = 0;
	};

	class DistanceOutput
	{
	  public:
		virtual void distance(Distance lenght) = 0;
	};
}
#endif
