#pragma once

namespace devuino::tools
{
	template<class T>
	class Span
	{
	  public:
		constexpr Span(const T minimum, const T maximum) : minimum {minimum}, maximum {maximum} {};

		T minimum;
		T maximum;

		constexpr friend bool operator==(Span<T> const& lhs, T const& rhs) { return (rhs >= lhs.minimum) && (rhs <= lhs.maximum); }
		constexpr friend bool operator==(T const& lhs, Span<T> const& rhs) { return (lhs >= rhs.minimum) && (lhs <= rhs.maximum); }

		constexpr friend bool operator!=(Span<T> const& lhs, T const& rhs) { return !(lhs == rhs); }
		constexpr friend bool operator!=(T const& lhs, Span<T> const& rhs) { return !(rhs == lhs); }
	};
}