#pragma once

namespace devuino
{
	template<class T>
	static constexpr T&& move(T& object) noexcept
	{
		return static_cast<T&&>(object);
	}
}