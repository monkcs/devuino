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

		operator uint8_t&()
		{
			return value;
		};

		constexpr operator uint8_t() const
		{
			return value;
		};

		constexpr Channel operator+() const
		{
			return *this;
		}

		Channel& operator+=(Channel const& rhs)
		{
			this->value += rhs.value;
			return *this;
		}

		Channel& operator-=(Channel const& rhs)
		{
			this->value -= rhs.value;
			return *this;
		}

		Channel& operator*=(Channel const& rhs)
		{
			this->value *= rhs.value;
			return *this;
		}

		Channel& operator/=(Channel const& rhs)
		{
			this->value /= rhs.value;
			return *this;
		}

		constexpr friend Channel operator+(Channel const& lhs, Channel const& rhs)
		{
			return Channel {static_cast<uint8_t>(lhs.value + rhs.value)};
		}

		constexpr friend Channel operator-(Channel const& lhs, Channel const& rhs)
		{
			return Channel {static_cast<uint8_t>(lhs.value - rhs.value)};
		}

		constexpr friend Channel operator*(Channel const& lhs, Channel const& rhs)
		{
			return Channel {static_cast<uint8_t>(lhs.value * rhs.value)};
		}

		constexpr friend Channel operator/(Channel const& lhs, Channel const& rhs)
		{
			return Channel {static_cast<uint8_t>(lhs.value / rhs.value)};
		}

		constexpr friend bool operator==(Channel const& lhs, Channel const& rhs)
		{
			return (lhs.value == rhs.value);
		}

		constexpr friend bool operator!=(Channel const& lhs, Channel const& rhs)
		{
			return !(lhs == rhs);
		}

		constexpr friend bool operator<(Channel const& lhs, Channel const& rhs)
		{
			return (lhs.value < rhs.value);
		}

		constexpr friend bool operator>(Channel const& lhs, Channel const& rhs)
		{
			return rhs < lhs;
		}

		constexpr friend bool operator<=(Channel const& lhs, Channel const& rhs)
		{
			return !(lhs > rhs);
		}

		constexpr friend bool operator>=(Channel const& lhs, Channel const& rhs)
		{
			return !(lhs < rhs);
		}
	};

	constexpr Channel operator""_channel(const unsigned long long int value)
	{
		return Channel {static_cast<uint8_t>(value)};
	};
}
