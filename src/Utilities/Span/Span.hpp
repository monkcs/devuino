#pragma once

namespace devuino::utilities
{
	template<typename Type>
	class Span
	{
	  public:
		constexpr Span(const Type minimum, const Type maximum) : minimum {minimum}, maximum {maximum} {};

		Type minimum;
		Type maximum;

		constexpr friend bool operator==(Span<Type> const& lhs, Type const& rhs) { return (rhs >= lhs.minimum) && (rhs <= lhs.maximum); }
		constexpr friend bool operator==(Type const& lhs, Span<Type> const& rhs) { return (lhs >= rhs.minimum) && (lhs <= rhs.maximum); }

		constexpr friend bool operator!=(Span<Type> const& lhs, Type const& rhs) { return !(lhs == rhs); }
		constexpr friend bool operator!=(Type const& lhs, Span<Type> const& rhs) { return !(rhs == lhs); }
	};
}