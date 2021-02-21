#pragma once

namespace devuino
{
	class Distance
	{
	  public:
		explicit constexpr Distance(const long double metre) : metre(metre) {};

		// Untill C++20
		// constexpr auto operator<=>(const Distance&) const = default;

		constexpr Distance operator-() const { return Distance {-this->metre}; };

		constexpr Distance operator+() const { return *this; };

		Distance& operator+=(Distance const& rhs)
		{
			this->metre += rhs.metre;
			return *this;
		};

		Distance& operator-=(Distance const& rhs)
		{
			this->metre -= rhs.metre;
			return *this;
		};

		Distance& operator*=(const long double rhs)
		{
			this->metre *= rhs;
			return *this;
		};

		Distance& operator/=(const long double rhs)
		{
			this->metre /= rhs;
			return *this;
		};

		constexpr friend Distance operator+(Distance const& lhs, Distance const& rhs) { return Distance {lhs.metre + rhs.metre}; };
		constexpr friend Distance operator-(Distance const& lhs, Distance const& rhs) { return Distance {lhs.metre - rhs.metre}; };

		constexpr friend long double operator*(Distance const& lhs, Distance const& rhs) { return lhs.metre * rhs.metre; };
		constexpr friend Distance operator*(Distance const& lhs, long double rhs) { return Distance {lhs.metre * rhs}; };

		constexpr friend long double operator/(Distance const& lhs, Distance const& rhs) { return lhs.metre / rhs.metre; };
		constexpr friend Distance operator/(Distance const& lhs, long double rhs) { return Distance {lhs.metre / rhs}; };

		constexpr friend bool operator==(Distance const& lhs, Distance const& rhs) { return lhs.metre == rhs.metre; };

		constexpr friend bool operator!=(Distance const& lhs, Distance const& rhs) { return !(lhs == rhs); };

		constexpr friend bool operator<(Distance const& lhs, Distance const& rhs) { return lhs.metre < rhs.metre; };

		constexpr friend bool operator>(Distance const& lhs, Distance const& rhs) { return rhs < lhs; };
		constexpr friend bool operator<=(Distance const& lhs, Distance const& rhs) { return !(lhs > rhs); };

		constexpr friend bool operator>=(Distance const& lhs, Distance const& rhs) { return !(lhs < rhs); };

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

				default: return 0.0;
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

				default: return 0.0;
			}
		};

	  protected:
		long double metre;
	};
	/* User defined litterals */

	constexpr Distance operator""_gigametre(const long double lenght) { return Distance {lenght * 1000000000.0}; }
	constexpr Distance operator""_gigametre(const long long int lenght) { return Distance {lenght * 1000000000.0}; }
	constexpr Distance operator""_Gm(const long double lenght) { return Distance {lenght * 1000000000.0}; }
	constexpr Distance operator""_Gm(const long long int lenght) { return Distance {lenght * 1000000000.0}; }

	constexpr Distance operator""_megametre(const long double lenght) { return Distance {lenght * 1000000.0}; }
	constexpr Distance operator""_megametre(const long long int lenght) { return Distance {lenght * 1000000.0}; }
	constexpr Distance operator""_Mm(const long double lenght) { return Distance {lenght * 1000000.0}; }
	constexpr Distance operator""_Mm(const long long int lenght) { return Distance {lenght * 1000000.0}; }

	constexpr Distance operator""_kilometre(const long double lenght) { return Distance {lenght * 1000.0}; }
	constexpr Distance operator""_kilometre(const long long int lenght) { return Distance {lenght * 1000.0}; }
	constexpr Distance operator""_km(const long double lenght) { return Distance {lenght * 1000.0}; }
	constexpr Distance operator""_km(const long long int lenght) { return Distance {lenght * 1000.0}; }

	constexpr Distance operator""_hektometre(const long double lenght) { return Distance {lenght * 100.0}; }
	constexpr Distance operator""_hektometre(const long long int lenght) { return Distance {lenght * 100.0}; }
	constexpr Distance operator""_hm(const long double lenght) { return Distance {lenght * 100.0}; }
	constexpr Distance operator""_hm(const long long int lenght) { return Distance {lenght * 100.0}; }

	constexpr Distance operator""_dekametre(const long double lenght) { return Distance {lenght * 10.0}; }
	constexpr Distance operator""_dekametre(const long long int lenght) { return Distance {lenght * 10.0}; }
	constexpr Distance operator""_dam(const long double lenght) { return Distance {lenght * 10.0}; }
	constexpr Distance operator""_dam(const long long int lenght) { return Distance {lenght * 10.0}; }

	constexpr Distance operator""_metre(const long double lenght) { return Distance {lenght}; }
	constexpr Distance operator""_metre(const long long int lenght) { return Distance {lenght}; }
	constexpr Distance operator""_m(const long double lenght) { return Distance {lenght}; }
	constexpr Distance operator""_m(const long long int lenght) { return Distance {lenght}; }

	constexpr Distance operator""_decimetre(const long double lenght) { return Distance {lenght / 10.0}; }
	constexpr Distance operator""_decimetre(const long long int lenght) { return Distance {lenght / 10.0}; }
	constexpr Distance operator""_dm(const long double lenght) { return Distance {lenght / 10.0}; }
	constexpr Distance operator""_dm(const long long int lenght) { return Distance {lenght / 10.0}; }

	constexpr Distance operator""_centimetre(const long double lenght) { return Distance {lenght / 100.0}; }
	constexpr Distance operator""_centimetre(const long long int lenght) { return Distance {lenght / 100.0}; }
	constexpr Distance operator""_cm(const long double lenght) { return Distance {lenght / 100.0}; }
	constexpr Distance operator""_cm(const long long int lenght) { return Distance {lenght / 100.0}; }

	constexpr Distance operator""_millimetre(const long double lenght) { return Distance {lenght / 1000.0}; }
	constexpr Distance operator""_millimetre(const long long int lenght) { return Distance {lenght / 1000.0}; }
	constexpr Distance operator""_mm(const long double lenght) { return Distance {lenght / 1000.0}; }
	constexpr Distance operator""_mm(const long long int lenght) { return Distance {lenght / 1000.0}; }

	constexpr Distance operator""_micrometre(const long double lenght) { return Distance {lenght / 1000000.0}; }
	constexpr Distance operator""_micrometre(const long long int lenght) { return Distance {lenght / 1000000.0}; }
	constexpr Distance operator""_um(const long double lenght) { return Distance {lenght / 1000000.0}; }
	constexpr Distance operator""_um(const long long int lenght) { return Distance {lenght / 1000000.0}; }

	constexpr Distance operator""_nanometre(const long double lenght) { return Distance {lenght / 1000000000.0}; }
	constexpr Distance operator""_nanometre(const long long int lenght) { return Distance {lenght / 1000000000.0}; }
	constexpr Distance operator""_nm(const long double lenght) { return Distance {lenght / 1000000000.0}; }
	constexpr Distance operator""_nm(const long long int lenght) { return Distance {lenght / 1000000000.0}; }

	constexpr Distance operator""_thou(const long double lenght) { return Distance {lenght * 0.0000254}; }
	constexpr Distance operator""_thou(const long long int lenght) { return Distance {lenght * 0.0000254}; }

	constexpr Distance operator""_inch(const long double lenght) { return Distance {lenght * 0.0254}; }
	constexpr Distance operator""_inch(const long long int lenght) { return Distance {lenght * 0.0254}; }

	constexpr Distance operator""_foot(const long double lenght) { return Distance {lenght * 0.3048}; }
	constexpr Distance operator""_foot(const long long int lenght) { return Distance {lenght * 0.3048}; }

	constexpr Distance operator""_yard(const long double lenght) { return Distance {lenght * 0.9144}; }
	constexpr Distance operator""_yard(const long long int lenght) { return Distance {lenght * 0.9144}; }

	constexpr Distance operator""_chain(const long double lenght) { return Distance {lenght * 20.1168}; }
	constexpr Distance operator""_chain(const long long int lenght) { return Distance {lenght * 20.1168}; }

	constexpr Distance operator""_furlong(const long double lenght) { return Distance {lenght * 201.168}; }
	constexpr Distance operator""_furlong(const long long int lenght) { return Distance {lenght * 201.168}; }

	constexpr Distance operator""_mile(const long double lenght) { return Distance {lenght * 1609.344}; }
	constexpr Distance operator""_mile(const long long int lenght) { return Distance {lenght * 1609.344}; }

	constexpr Distance operator""_nautical(const long double lenght) { return Distance {lenght * 1852.0}; }
	constexpr Distance operator""_nautical(const long long int lenght) { return Distance {lenght * 1852.0}; }

}