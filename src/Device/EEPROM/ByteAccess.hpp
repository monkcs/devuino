#pragma once

#include "../../Utilities/Move/Move.hpp"
#include "../../Utilities/Storage/Storage.hpp"

#include <stdint.h>

namespace devuino::device
{
	template<typename EepromBackend>
	class ByteAccessReadonly
	{
		const EepromBackend& backend;
		uint16_t address;

	  public:
		constexpr ByteAccessReadonly(EepromBackend& backend, const uint16_t address) : backend {backend}, address {address} { }

		constexpr operator uint8_t() const { return read(); }

		constexpr bool operator==(const ByteAccessReadonly& rhs) const { return read() == rhs.read(); }
		constexpr bool operator!=(const ByteAccessReadonly& rhs) const { return !operator==(rhs); }

		/// @brief Read the value at the current address
		constexpr uint8_t read() const { return backend.read(address); }
	};

	template<typename EepromBackend>
	class ByteAccess
	{
		EepromBackend& backend;
		uint16_t address;

	  public:
		constexpr ByteAccess(EepromBackend& backend, const uint16_t address) : backend {backend}, address {address} { }

		constexpr operator uint8_t() { return read(); }

		/// @brief Update the value if the new one is different from the old one
		constexpr ByteAccess& operator=(const uint8_t data)
		{
			update(data);
			return *this;
		}
		constexpr ByteAccess& operator+=(const uint8_t rhs)
		{
			write(read() + rhs);
			return *this;
		}
		constexpr ByteAccess operator-=(const uint8_t rhs)
		{
			write(read() - rhs);
			return *this;
		}
		constexpr ByteAccess operator*=(const uint8_t rhs)
		{
			write(read() * rhs);
			return *this;
		}
		constexpr ByteAccess operator/=(const uint8_t rhs)
		{
			write(read() / rhs);
			return *this;
		}
		constexpr ByteAccess operator^=(const uint8_t rhs)
		{
			write(read() ^ rhs);
			return *this;
		}
		constexpr ByteAccess operator%=(const uint8_t rhs)
		{
			write(read() % rhs);
			return *this;
		}
		constexpr ByteAccess operator&=(const uint8_t rhs)
		{
			write(read() & rhs);
			return *this;
		}
		constexpr ByteAccess operator|=(const uint8_t rhs)
		{
			write(read() | rhs);
			return *this;
		}
		constexpr ByteAccess operator<<=(const uint8_t rhs)
		{
			write(read() << rhs);
			return *this;
		}
		constexpr ByteAccess operator>>=(const uint8_t rhs)
		{
			write(read() >> rhs);
			return *this;
		}

		constexpr ByteAccess operator++() { return operator+=(1); }
		constexpr ByteAccess operator--() { return operator-=(1); }
		constexpr uint8_t operator++(int)
		{
			const auto result = read();
			operator++();
			return result;
		}
		constexpr uint8_t operator--(int)
		{
			const auto result = read();
			operator--();
			return result;
		}

		constexpr bool operator==(const ByteAccess& rhs) { return read() == rhs.read(); }
		constexpr bool operator!=(const ByteAccess& rhs) { return !operator==(rhs); }

		/// @brief Update the value if the new one is different from the old one
		/// @param value The data to store at the current address
		constexpr void update(const uint8_t value)
		{
			if (backend.read(address) != value)
			{
				backend.write(address, value);
			}
		}

		/// @brief Read the value at the current address
		constexpr uint8_t read() { return backend.read(address); }

		/// @brief Write the value at the current address
		/// @param value The data to store
		constexpr void write(const uint8_t value) { backend.write(address, value); }
	};
}