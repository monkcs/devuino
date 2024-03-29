#pragma once

namespace devuino::utilities
{
	class Lenght
	{
		long double metre;

	  public:
		explicit constexpr Lenght(const long double metre = {}) : metre {metre} {};

		// Untill C++20
		// constexpr auto operator<=>(const Lenght&) const = default;

		constexpr Lenght operator-() const { return Lenght {-this->metre}; };
		constexpr Lenght operator+() const { return *this; }

		constexpr Lenght& operator+=(Lenght const& rhs)
		{
			this->metre += rhs.metre;
			return *this;
		};

		constexpr Lenght& operator-=(Lenght const& rhs)
		{
			this->metre -= rhs.metre;
			return *this;
		};

		constexpr Lenght& operator*=(const long double rhs)
		{
			this->metre *= rhs;
			return *this;
		};

		constexpr Lenght& operator/=(const long double rhs)
		{
			this->metre /= rhs;
			return *this;
		};

		constexpr friend Lenght operator+(Lenght const& lhs, Lenght const& rhs) { return Lenght {lhs.metre + rhs.metre}; };
		constexpr friend Lenght operator-(Lenght const& lhs, Lenght const& rhs) { return Lenght {lhs.metre - rhs.metre}; };

		constexpr friend Lenght operator*(const long double lhs, Lenght const& rhs) { return Lenght {lhs * rhs.metre}; };
		constexpr friend Lenght operator*(Lenght const& lhs, const long double rhs) { return Lenght {lhs.metre * rhs}; };

		constexpr friend Lenght operator/(Lenght const& lhs, const long double rhs) { return Lenght {lhs.metre / rhs}; };

		constexpr friend bool operator==(Lenght const& lhs, Lenght const& rhs) { return lhs.metre == rhs.metre; };
		constexpr friend bool operator!=(Lenght const& lhs, Lenght const& rhs) { return !(lhs == rhs); };

		constexpr friend bool operator<(Lenght const& lhs, Lenght const& rhs) { return lhs.metre < rhs.metre; };
		constexpr friend bool operator>(Lenght const& lhs, Lenght const& rhs) { return rhs.metre > lhs.metre; };

		constexpr friend bool operator<=(Lenght const& lhs, Lenght const& rhs) { return !(lhs > rhs); };
		constexpr friend bool operator>=(Lenght const& lhs, Lenght const& rhs) { return !(lhs < rhs); };

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

		constexpr long double as(const Imperial unit) const
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
		}

		constexpr long double as(const SI unit) const
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
		}
	};

	/* User defined litterals */

	constexpr Lenght operator""_gigametre(const long double lenght) { return Lenght {lenght * 1000000000.0}; }
	constexpr Lenght operator""_gigametre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) * 1000000000.0};
	}

	constexpr Lenght operator""_Gm(const long double lenght) { return Lenght {lenght * 1000000000.0}; }
	constexpr Lenght operator""_Gm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 1000000000.0}; }

	constexpr Lenght operator""_megametre(const long double lenght) { return Lenght {lenght * 1000000.0}; }
	constexpr Lenght operator""_megametre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) * 1000000.0};
	}

	constexpr Lenght operator""_Mm(const long double lenght) { return Lenght {lenght * 1000000.0}; }
	constexpr Lenght operator""_Mm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 1000000.0}; }

	constexpr Lenght operator""_kilometre(const long double lenght) { return Lenght {lenght * 1000.0}; }
	constexpr Lenght operator""_kilometre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) * 1000.0};
	}

	constexpr Lenght operator""_km(const long double lenght) { return Lenght {lenght * 1000.0}; }
	constexpr Lenght operator""_km(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 1000.0}; }

	constexpr Lenght operator""_hektometre(const long double lenght) { return Lenght {lenght * 100.0}; }
	constexpr Lenght operator""_hektometre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) * 100.0};
	}

	constexpr Lenght operator""_hm(const long double lenght) { return Lenght {lenght * 100.0}; }
	constexpr Lenght operator""_hm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 100.0}; }

	constexpr Lenght operator""_dekametre(const long double lenght) { return Lenght {lenght * 10.0}; }
	constexpr Lenght operator""_dekametre(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 10.0}; }

	constexpr Lenght operator""_dam(const long double lenght) { return Lenght {lenght * 10.0}; }
	constexpr Lenght operator""_dam(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 10.0}; }

	constexpr Lenght operator""_metre(const long double lenght) { return Lenght {lenght}; }
	constexpr Lenght operator""_metre(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght)}; }

	constexpr Lenght operator""_m(const long double lenght) { return Lenght {lenght}; }
	constexpr Lenght operator""_m(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght)}; }

	constexpr Lenght operator""_decimetre(const long double lenght) { return Lenght {lenght / 10.0}; }
	constexpr Lenght operator""_decimetre(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) / 10.0}; }

	constexpr Lenght operator""_dm(const long double lenght) { return Lenght {lenght / 10.0}; }
	constexpr Lenght operator""_dm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) / 10.0}; }

	constexpr Lenght operator""_centimetre(const long double lenght) { return Lenght {lenght / 100.0}; }
	constexpr Lenght operator""_centimetre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) / 100.0};
	}

	constexpr Lenght operator""_cm(const long double lenght) { return Lenght {lenght / 100.0}; }
	constexpr Lenght operator""_cm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) / 100.0}; }

	constexpr Lenght operator""_millimetre(const long double lenght) { return Lenght {lenght / 1000.0}; }
	constexpr Lenght operator""_millimetre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) / 1000.0};
	}

	constexpr Lenght operator""_mm(const long double lenght) { return Lenght {lenght / 1000.0}; }
	constexpr Lenght operator""_mm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) / 1000.0}; }

	constexpr Lenght operator""_micrometre(const long double lenght) { return Lenght {lenght / 1000000.0}; }
	constexpr Lenght operator""_micrometre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) / 1000000.0};
	}

	constexpr Lenght operator""_um(const long double lenght) { return Lenght {lenght / 1000000.0}; }
	constexpr Lenght operator""_um(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) / 1000000.0}; }

	constexpr Lenght operator""_nanometre(const long double lenght) { return Lenght {lenght / 1000000000.0}; }
	constexpr Lenght operator""_nanometre(const unsigned long long int lenght)
	{
		return Lenght {static_cast<long double>(lenght) / 1000000000.0};
	}

	constexpr Lenght operator""_nm(const long double lenght) { return Lenght {lenght / 1000000000.0}; }
	constexpr Lenght operator""_nm(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) / 1000000000.0}; }

	constexpr Lenght operator""_thou(const long double lenght) { return Lenght {lenght * 0.0000254}; }
	constexpr Lenght operator""_thou(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 0.0000254}; }

	constexpr Lenght operator""_inch(const long double lenght) { return Lenght {lenght * 0.0254}; }
	constexpr Lenght operator""_inch(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 0.0254}; }

	constexpr Lenght operator""_foot(const long double lenght) { return Lenght {lenght * 0.3048}; }
	constexpr Lenght operator""_foot(const unsigned long long int lenght) { return Lenght {lenght * 0.3048}; }

	constexpr Lenght operator""_yard(const long double lenght) { return Lenght {lenght * 0.9144}; }
	constexpr Lenght operator""_yard(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 0.9144}; }

	constexpr Lenght operator""_chain(const long double lenght) { return Lenght {lenght * 20.1168}; }
	constexpr Lenght operator""_chain(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 20.1168}; }

	constexpr Lenght operator""_furlong(const long double lenght) { return Lenght {lenght * 201.168}; }
	constexpr Lenght operator""_furlong(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 201.168}; }

	constexpr Lenght operator""_mile(const long double lenght) { return Lenght {lenght * 1609.344}; }
	constexpr Lenght operator""_mile(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 1609.344}; }

	constexpr Lenght operator""_nautical(const long double lenght) { return Lenght {lenght * 1852.0}; }
	constexpr Lenght operator""_nautical(const unsigned long long int lenght) { return Lenght {static_cast<long double>(lenght) * 1852.0}; }
}