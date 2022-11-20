#pragma once

namespace devuino::utilities
{
	class Temperature
	{
		long double temperature;

	  public:
		explicit constexpr Temperature(const long double celsius = {}) : temperature {celsius} {};

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
			// return (unit == Unit::Celsius) ? celsius() : ((unit == Unit::Fahrenheit) ? fahrenheit() : kelvin());

			switch (unit)
			{
				case Unit::Fahrenheit: return fahrenheit();
				case Unit::Kelvin: return kelvin();

				case Unit::Celsius:
				default: return celsius();
			}
		};

		constexpr long double celsius() const { return temperature; };
		constexpr long double fahrenheit() const { return temperature * (9.0 / 5.0) + 32.0; };
		constexpr long double kelvin() const { return temperature + 273.15; };

		constexpr Temperature operator-() const { return Temperature {-this->temperature}; }
		constexpr Temperature operator+() const { return *this; }

		constexpr Temperature& operator+=(Temperature const& rhs)
		{
			this->temperature += rhs.temperature;
			return *this;
		}

		constexpr Temperature& operator-=(Temperature const& rhs)
		{
			this->temperature -= rhs.temperature;
			return *this;
		}

		constexpr Temperature& operator*=(const long double rhs)
		{
			this->temperature *= rhs;
			return *this;
		}

		constexpr Temperature& operator/=(const long double rhs)
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

		constexpr friend bool operator==(Temperature const& lhs, Temperature const& rhs) { return (lhs.temperature == rhs.temperature); }
		constexpr friend bool operator!=(Temperature const& lhs, Temperature const& rhs) { return !(lhs == rhs); }
		constexpr friend bool operator<(Temperature const& lhs, Temperature const& rhs) { return (lhs.temperature < rhs.temperature); }
		constexpr friend bool operator>(Temperature const& lhs, Temperature const& rhs) { return rhs < lhs; }
		constexpr friend bool operator<=(Temperature const& lhs, Temperature const& rhs) { return !(lhs > rhs); }
		constexpr friend bool operator>=(Temperature const& lhs, Temperature const& rhs) { return !(lhs < rhs); }
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