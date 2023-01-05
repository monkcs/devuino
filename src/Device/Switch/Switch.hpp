#pragma once

#include "../../Onboard/Digital.hpp"
#include "../../Utilities/Move/Move.hpp"

namespace devuino::device
{
	/// @brief Switch is a generic digital output
	/// @tparam DigitalBackend Physical or logical pin
	template<typename DigitalBackend = devuino::onboard::DigitalOutput>
	class Switch
	{
		DigitalBackend pin;
		bool valid = true;

	  public:
		/// @brief Switch is a generic digital output
		/// @param pin Physical or logical pin
		/// @param initial Initial value of switch
		constexpr Switch(DigitalBackend&& pin, const bool initial = false) : pin {devuino::move(pin)} { this->pin = initial; }

		Switch(Switch&) = delete;
		Switch& operator=(Switch&) = delete;

		constexpr Switch(Switch&& other) noexcept : pin {devuino::move(other.pin)} { other.valid = false; }
		constexpr Switch& operator=(Switch&& other) noexcept
		{
			if (valid)
			{
				pin = false;
			}

			pin = devuino::move(other.pin);

			valid = true;
			other.valid = false;

			return *this;
		}

		~Switch()
		{
			if (valid)
			{
				pin = false;
			}
		}

		/// @brief Value of switch
		constexpr operator bool() const { return pin; }

		/// @brief Set value of switch
		constexpr Switch& operator=(const bool value)
		{
			pin = value;
			return *this;
		}

		/// @brief Turn switch off
		constexpr void off() { pin = false; }
		/// @brief Turn switch on
		constexpr void on() { pin = true; }

		/// @brief Toggle switch
		constexpr void toggle() { pin.toggle(); }
	};
}