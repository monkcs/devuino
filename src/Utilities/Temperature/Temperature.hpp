#pragma once

namespace devuino::utilities
{
	class Temperature
	{
	  public:
		enum class Unit
		{
			Celsius,
			Fahrenheit,
			Kelvin
		};

	  private:
		long double temperature;

		constexpr auto convert(const Unit origin, const long double value) const
		{
			switch (origin)
			{
				case Unit::Fahrenheit: return (value - 32.0) * (5.0 / 9.0);
				case Unit::Kelvin: return value - 273.15;

				case Unit::Celsius:
				default: return value;
			}
		}

		explicit constexpr Temperature(const long double temperature = {}) : temperature {temperature} {};

	  public:
		explicit constexpr Temperature(const Unit unit, const long double temperature = {}) : temperature {convert(unit, temperature)} {};

		// Untill C++20
		// constexpr auto operator<=>(const Temperature&) const = default;

		constexpr long double as(const Unit unit) const
		{
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

		constexpr Temperature operator-() const { return Temperature {-temperature}; }
		constexpr Temperature operator+() const { return *this; }

		constexpr Temperature& operator+=(Temperature const& rhs) { return temperature += rhs.temperature, *this; }
		constexpr Temperature& operator-=(Temperature const& rhs) { return temperature -= rhs.temperature, *this; }
		constexpr Temperature& operator*=(const long double rhs) { return temperature *= rhs, *this; }
		constexpr Temperature& operator/=(const long double rhs) { return temperature /= rhs, *this; }

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

	constexpr Temperature operator""_C(const long double celsius) { return Temperature {Temperature::Unit::Celsius, celsius}; }
	constexpr Temperature operator""_C(const unsigned long long int celsius)
	{
		return Temperature {Temperature::Unit::Celsius, static_cast<long double>(celsius)};
	}
	constexpr Temperature operator""_celsius(const long double celsius) { return Temperature {Temperature::Unit::Celsius, celsius}; }
	constexpr Temperature operator""_celsius(const unsigned long long int celsius)
	{
		return Temperature {Temperature::Unit::Celsius, static_cast<long double>(celsius)};
	}

	constexpr Temperature operator""_F(const long double fahrenheit) { return Temperature {Temperature::Unit::Fahrenheit, fahrenheit}; }
	constexpr Temperature operator""_F(const unsigned long long int fahrenheit)
	{
		return Temperature {Temperature::Unit::Fahrenheit, fahrenheit};
	}
	constexpr Temperature operator""_fahrenheit(const long double fahrenheit)
	{
		return Temperature {Temperature::Unit::Fahrenheit, fahrenheit};
	}
	constexpr Temperature operator""_fahrenheit(const unsigned long long int fahrenheit)
	{
		return Temperature {Temperature::Unit::Fahrenheit, fahrenheit};
	}

	constexpr Temperature operator""_K(const long double kelvin) { return Temperature {Temperature::Unit::Kelvin, kelvin}; }
	constexpr Temperature operator""_K(const unsigned long long int kelvin)
	{
		return Temperature {Temperature::Unit::Kelvin, static_cast<long double>(kelvin)};
	}
	constexpr Temperature operator""_kelvin(const long double kelvin) { return Temperature {Temperature::Unit::Kelvin, kelvin}; }
	constexpr Temperature operator""_kelvin(const unsigned long long int kelvin)
	{
		return Temperature {Temperature::Unit::Kelvin, static_cast<long double>(kelvin)};
	}
}