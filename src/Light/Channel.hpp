#pragma once

#include <stdint.h>

namespace devuino
{
	class Channel
	{
	  protected:
		uint8_t value;

	  public:
		explicit constexpr Channel(const uint8_t value) : value {value} {};

		operator uint8_t&() { return value; };

		constexpr operator uint8_t() const { return value; };

		Channel& operator+=(const Channel& rhs)
		{
			this->value += rhs.value;
			return *this;
		}

		Channel& operator-=(const Channel& rhs)
		{
			this->value -= rhs.value;
			return *this;
		}

		Channel& operator*=(const uint8_t rhs)
		{
			this->value *= rhs;
			return *this;
		}

		Channel& operator/=(const uint8_t rhs)
		{
			this->value /= rhs;
			return *this;
		}

		constexpr friend Channel operator+(const Channel& lhs, const Channel& rhs) { return Channel {static_cast<uint8_t>(lhs.value + rhs.value)}; }

		constexpr friend Channel operator-(const Channel& lhs, const Channel& rhs) { return Channel {static_cast<uint8_t>(lhs.value - rhs.value)}; }

		constexpr friend Channel operator*(const Channel& lhs, const Channel& rhs) { return Channel {static_cast<uint8_t>(lhs.value * rhs.value)}; }
		constexpr friend Channel operator*(const Channel& lhs, const uint8_t rhs) { return Channel {static_cast<uint8_t>(lhs.value * rhs)}; }

		constexpr friend Channel operator/(const Channel& lhs, const Channel& rhs) { return Channel {static_cast<uint8_t>(lhs.value / rhs.value)}; }
		constexpr friend Channel operator/(const Channel& lhs, const uint8_t rhs) { return Channel {static_cast<uint8_t>(lhs.value / rhs)}; }

		constexpr friend bool operator==(const Channel& lhs, const Channel& rhs) { return (lhs.value == rhs.value); }

		constexpr friend bool operator!=(const Channel& lhs, const Channel& rhs) { return !(lhs == rhs); }

		constexpr friend bool operator<(const Channel& lhs, const Channel& rhs) { return (lhs.value < rhs.value); }

		constexpr friend bool operator>(const Channel& lhs, const Channel& rhs) { return rhs < lhs; }

		constexpr friend bool operator<=(const Channel& lhs, const Channel& rhs) { return !(lhs > rhs); }

		constexpr friend bool operator>=(const Channel& lhs, const Channel& rhs) { return !(lhs < rhs); }
	};

	constexpr Channel operator""_channel(const unsigned long long int value) { return Channel {static_cast<uint8_t>(value)}; };
}
