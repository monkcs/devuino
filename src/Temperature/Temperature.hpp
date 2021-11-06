#pragma once

namespace devuino
{
	class Temperature
	{
	  public:
		explicit constexpr Temperature(const long double celsius) : temperature {celsius} {};

		// Untill C++20
		// constexpr auto operator<=>(const Temperature&) const = default;

		enum class Unit
		{
			Celsius,
			Fahrenheit,
			Kelvin
		};

		constexpr long double as(const Unit unit) const
		{
			return (unit == Unit::Celsius) ? celsius() : ((unit == Unit::Fahrenheit) ? fahrenheit() : kelvin());

			/* After C++14
				switch (unit)
				{
					case Unit::Celsius: return celsius();
					case Unit::Fahrenheit: return fahrenheit();
					case Unit::Kelvin: return kelvin();
				}
			*/
		};

		constexpr long double celsius() const { return temperature; };
		constexpr long double fahrenheit() const { return temperature * (9.0 / 5.0) + 32.0; };
		constexpr long double kelvin() const { return temperature + 273.15; };

		constexpr Temperature operator-() const { return Temperature {-this->temperature}; }
		constexpr Temperature operator+() const { return *this; }

		Temperature& operator+=(Temperature const& rhs)
		{
			this->temperature += rhs.temperature;
			return *this;
		}

		Temperature& operator-=(Temperature const& rhs)
		{
			this->temperature -= rhs.temperature;
			return *this;
		}

		Temperature& operator*=(const int rhs)
		{
			this->temperature *= rhs;
			return *this;
		}

		Temperature& operator/=(const int rhs)
		{
			this->temperature /= rhs;
			return *this;
		}

		constexpr friend Temperature operator+(Temperature const& lhs, Temperature const& rhs)
		{
			return Temperature {lhs.temperature + rhs.temperature};
		}
		constexpr friend Temperature operator-(Temperature const& lhs, Temperature const& rhs)
		{
			return Temperature {lhs.temperature - rhs.temperature};
		}

		constexpr friend Temperature operator*(const int lhs, Temperature const& rhs) { return Temperature {lhs * rhs.temperature}; }
		constexpr friend Temperature operator*(Temperature const& lhs, const int rhs) { return Temperature {lhs.temperature * rhs}; }

		constexpr friend Temperature operator/(Temperature const& lhs, const int rhs) { return Temperature {lhs.temperature / rhs}; }

		constexpr friend bool operator==(Temperature const& lhs, Temperature const& rhs) { return (lhs.temperature == rhs.temperature); }
		constexpr friend bool operator!=(Temperature const& lhs, Temperature const& rhs) { return !(lhs == rhs); }
		constexpr friend bool operator<(Temperature const& lhs, Temperature const& rhs) { return (lhs.temperature < rhs.temperature); }
		constexpr friend bool operator>(Temperature const& lhs, Temperature const& rhs) { return rhs < lhs; }
		constexpr friend bool operator<=(Temperature const& lhs, Temperature const& rhs) { return !(lhs > rhs); }
		constexpr friend bool operator>=(Temperature const& lhs, Temperature const& rhs) { return !(lhs < rhs); }

	  protected:
		long double temperature;
	};

	/* User defined litterals */

	constexpr Temperature operator""_C(const long double celsius) { return Temperature {celsius}; }
	constexpr Temperature operator""_C(const unsigned long long int celsius) { return Temperature {static_cast<long double>(celsius)}; }
	constexpr Temperature operator""_celsius(const long double celsius) { return Temperature {celsius}; }
	constexpr Temperature operator""_celsius(const unsigned long long int celsius)
	{
		return Temperature {static_cast<long double>(celsius)};
	}

	constexpr Temperature operator""_F(const long double fahrenheit) { return Temperature {(fahrenheit - 32) * (5.0 / 9.0)}; }
	constexpr Temperature operator""_F(const unsigned long long int fahrenheit)
	{
		return Temperature {(static_cast<long double>(fahrenheit) - 32) * (5.0 / 9.0)};
	}
	constexpr Temperature operator""_fahrenheit(const long double fahrenheit) { return Temperature {(fahrenheit - 32) * (5.0 / 9.0)}; }
	constexpr Temperature operator""_fahrenheit(const unsigned long long int fahrenheit)
	{
		return Temperature {(static_cast<long double>(fahrenheit) - 32) * (5.0 / 9.0)};
	}

	constexpr Temperature operator""_K(const long double kelvin) { return Temperature {kelvin - 273.15}; }
	constexpr Temperature operator""_K(const unsigned long long int kelvin)
	{
		return Temperature {static_cast<long double>(kelvin) - 273.15};
	}
	constexpr Temperature operator""_kelvin(const long double kelvin) { return Temperature {kelvin - 273.15}; }
	constexpr Temperature operator""_kelvin(const unsigned long long int kelvin)
	{
		return Temperature {static_cast<long double>(kelvin) - 273.15};
	}
}