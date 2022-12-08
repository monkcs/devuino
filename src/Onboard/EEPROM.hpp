#pragma once

#include "../Utilities/Storage/Storage.hpp"

#include <stdint.h>

namespace devuino::onboard
{
	template<int lenght, typename EepromBackend>
	class EEPROM
	{
		static_assert(lenght > 0, "Storage size of EEPROM needs to be larger than zero");
		static_assert(lenght <= 256, "Current implementation cannot handle larger storage size than 256");

		EepromBackend backend;

		template<int allocation = lenght, int offset = 0>
		class Allocation
		{
			static_assert((allocation >= 0) && (offset >= 0), "Allocation size and offset cannot be negative");
			static_assert((allocation + offset) <= lenght, "Storage size + offset cannot be larger than EEPROM size");

			EepromBackend& backend;

			class ByteAccess
			{
				EepromBackend& backend;
				uint8_t address;

			  public:
				constexpr ByteAccess(EepromBackend& backend, const uint8_t address) : backend {backend}, address {address} { }

				operator uint8_t() const { return read(); }

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

				constexpr bool operator==(const ByteAccess& rhs) const { return read() == rhs.read(); }
				constexpr bool operator!=(const ByteAccess& rhs) const { return !operator==(rhs); }

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
				constexpr uint8_t read() const { return backend.read(address); }

				/// @brief Write the value at the current address
				/// @param value The data to store
				constexpr void write(const uint8_t value) { backend.write(address, value); }
			};

			template<typename Type>
			class Iterator
			{
			  public:
				EepromBackend& backend;
				int address;

				constexpr Type operator*() { return Type {backend, static_cast<uint8_t>(address)}; }

				constexpr bool operator==(const Iterator& rhs) const { return address == rhs.address; }
				constexpr bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }

				constexpr void operator++() { ++address; }
			};
			template<typename Type>
			class ReverseIterator
			{
			  public:
				EepromBackend& backend;
				int address;

				constexpr Type operator*() { return Type {backend, static_cast<uint8_t>(address)}; }

				constexpr bool operator==(const ReverseIterator& rhs) const { return address == rhs.address; }
				constexpr bool operator!=(const ReverseIterator& rhs) const { return !operator==(rhs); }

				constexpr void operator++() { --address; }
			};

		  public:
			constexpr Allocation(EepromBackend& backend) : backend {backend} { }

			/// @brief Size in bytes of allocation
			static constexpr int size() { return allocation; }

			/// @brief Erase (set to zero) all bytes in allocation
			constexpr void erase() { fill(0); }

			/// @brief Fill all bytes in allocation
			/// @param value Value to fill
			constexpr void fill(const uint8_t value)
			{
				for (auto i : *this)
				{
					i = value;
				}
			}

			constexpr const ByteAccess front() const { return {backend, offset}; }
			constexpr ByteAccess front() { return {backend, offset}; }

			constexpr const ByteAccess back() const { return {backend, offset + allocation - 1}; }
			constexpr ByteAccess back() { return {backend, offset + allocation - 1}; }

			constexpr Iterator<const ByteAccess> begin() const { return {backend, offset}; }
			constexpr Iterator<const ByteAccess> end() const { return {backend, offset + allocation}; }
			constexpr Iterator<ByteAccess> begin() { return {backend, offset}; }
			constexpr Iterator<ByteAccess> end() { return {backend, offset + allocation}; }

			constexpr ReverseIterator<const ByteAccess> rbegin() const { return {backend, offset + allocation - 1}; }
			constexpr ReverseIterator<const ByteAccess> rend() const { return {backend, offset - 1}; }
			constexpr ReverseIterator<ByteAccess> rbegin() { return {backend, offset + allocation - 1}; }
			constexpr ReverseIterator<ByteAccess> rend() { return {backend, offset - 1}; }

			constexpr const ByteAccess operator[](const uint8_t address) const { return {backend, address}; }
			constexpr ByteAccess operator[](const uint8_t address) { return {backend, address}; }
		};

	  public:
		constexpr EEPROM(const EepromBackend backend) : backend {backend} { }

		EEPROM(const EEPROM&) = delete;
		EEPROM& operator=(const EEPROM&) = delete;

		/// @brief Allocation of raw EEPROM storage
		/// @tparam allocation Size of allocation in bytes
		/// @tparam offset Offset from begining of EEPROM storage in bytes
		template<int allocation = lenght, int offset = 0>
		constexpr auto raw()
		{
			return Allocation<allocation, offset> {backend};
		}

		/// @brief Allocation of raw const EEPROM storage
		/// @tparam allocation Size of allocation in bytes
		/// @tparam offset Offset from begining of EEPROM storage in bytes
		template<int allocation = lenght, int offset = 0>
		constexpr const auto raw() const
		{
			return Allocation<allocation, offset> {backend};
		}

		template<typename Structure, int offset = 0>
		constexpr auto managed()
		{
			return Storage<Structure, Allocation<sizeof(Structure), offset>> {backend};
		}

		/*
		template<typename Structure, int offset = 0>
		constexpr auto managed() const
		{
			return StorageReadonly<Structure, Allocation<sizeof(Structure), offset>> {backend};
		}
		*/
	};
}
