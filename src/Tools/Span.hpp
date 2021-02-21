#pragma once

namespace Devuino
{
	namespace tools
	{
		template<class T>
		class Span
		{
		  private:
			T minimum;
			T maximum;

		  public:
			constexpr Span(const T minimum, const T maximum) : minimum {minimum}, maximum {maximum} {};

			constexpr friend bool operator==(Span<T> const& lhs, T const& rhs) { return (rhs >= lhs.minimum) && (rhs <= lhs.maximum); }
			constexpr friend bool operator==(T const& lhs, Span<T> const& rhs) { return (lhs >= rhs.minimum) && (lhs <= rhs.maximum); }

			constexpr friend bool operator!=(Span<T> const& lhs, T const& rhs) { return !(lhs == rhs); }
			constexpr friend bool operator!=(T const& lhs, Span<T> const& rhs) { return !(rhs == lhs); }
		};
	}
}