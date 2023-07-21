#pragma once

#include "../../Utilities/Move/Move.hpp"
#include "../../Utilities/Storage/Storage.hpp"
#include "ByteAccess.hpp"

#include <stdint.h>

namespace devuino::device
{
	/// @brief Allocation is a allocation of raw EEPROM storage
	/// @tparam EepromBackend Physical or logical backend
	/// @tparam allocation Size of allocation in bytes
	/// @tparam offset Offset from begining of EEPROM storage in bytes
	template<typename EepromBackend, int allocation, int offset = 0>
	class Allocation
	{
		static_assert((allocation >= 0) && (offset >= 0), "Allocation size and offset cannot be negative");
		static_assert((allocation + offset) <= EepromBackend::lenght, "Storage size + offset cannot be larger than EEPROM size");

		EepromBackend& backend;

		template<typename Type>
		class Iterator
		{
		  public:
			EepromBackend& backend;
			uint16_t address;

			constexpr Type operator*() { return Type {backend, address}; }

			constexpr bool operator==(const Iterator& rhs) const { return address == rhs.address; }
			constexpr bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }

			constexpr void operator++() { ++address; }
		};
		template<typename Type>
		class ReverseIterator
		{
		  public:
			EepromBackend& backend;
			uint16_t address;

			constexpr Type operator*() { return Type {backend, address}; }

			constexpr bool operator==(const ReverseIterator& rhs) const { return address == rhs.address; }
			constexpr bool operator!=(const ReverseIterator& rhs) const { return !operator==(rhs); }

			constexpr void operator++() { --address; }
		};

	  public:
		constexpr Allocation(EepromBackend& backend) : backend {backend} { }

		/// @brief Size in bytes of allocation
		constexpr static int size() { return allocation; }

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

		constexpr ByteAccessReadonly<EepromBackend> front() const { return {backend, offset}; }
		constexpr ByteAccess<EepromBackend> front() { return {backend, offset}; }

		constexpr ByteAccessReadonly<EepromBackend> back() const { return {backend, offset + allocation - 1}; }
		constexpr ByteAccess<EepromBackend> back() { return {backend, offset + allocation - 1}; }

		constexpr Iterator<const ByteAccessReadonly<EepromBackend>> begin() const { return {backend, offset}; }
		constexpr Iterator<const ByteAccessReadonly<EepromBackend>> end() const { return {backend, offset + allocation}; }
		constexpr Iterator<ByteAccess<EepromBackend>> begin() { return {backend, offset}; }
		constexpr Iterator<ByteAccess<EepromBackend>> end() { return {backend, offset + allocation}; }

		constexpr ReverseIterator<const ByteAccessReadonly<EepromBackend>> rbegin() const { return {backend, offset + allocation - 1}; }
		constexpr ReverseIterator<const ByteAccessReadonly<EepromBackend>> rend() const { return {backend, offset - 1}; }
		constexpr ReverseIterator<ByteAccess<EepromBackend>> rbegin() { return {backend, offset + allocation - 1}; }
		constexpr ReverseIterator<ByteAccess<EepromBackend>> rend() { return {backend, offset - 1}; }

		constexpr ByteAccessReadonly<EepromBackend> operator[](const uint16_t address) const { return {backend, address}; }
		constexpr ByteAccess<EepromBackend> operator[](const uint16_t address) { return {backend, address}; }
	};

	/// @brief AllocationReadonly is a read-only allocation of raw EEPROM storage
	/// @tparam EepromBackend Physical or logical backend
	/// @tparam allocation Size of allocation in bytes
	/// @tparam offset Offset from begining of EEPROM storage in bytes
	template<typename EepromBackend, int allocation, int offset = 0>
	class AllocationReadonly
	{
		static_assert((allocation >= 0) && (offset >= 0), "Allocation size and offset cannot be negative");
		static_assert((allocation + offset) <= EepromBackend::lenght, "Storage size + offset cannot be larger than EEPROM size");

		const EepromBackend& backend;

		template<typename Type>
		class Iterator
		{
		  public:
			EepromBackend& backend;
			uint16_t address;

			constexpr Type operator*() { return Type {backend, address}; }

			constexpr bool operator==(const Iterator& rhs) const { return address == rhs.address; }
			constexpr bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }

			constexpr void operator++() { ++address; }
		};
		template<typename Type>
		class ReverseIterator
		{
		  public:
			EepromBackend& backend;
			uint16_t address;

			constexpr Type operator*() { return Type {backend, address}; }

			constexpr bool operator==(const ReverseIterator& rhs) const { return address == rhs.address; }
			constexpr bool operator!=(const ReverseIterator& rhs) const { return !operator==(rhs); }

			constexpr void operator++() { --address; }
		};

	  public:
		constexpr AllocationReadonly(const EepromBackend& backend) : backend {backend} { }

		/// @brief Size in bytes of allocation
		constexpr static int size() { return allocation; }

		constexpr ByteAccessReadonly<const EepromBackend> front() const { return {backend, offset}; }
		constexpr ByteAccessReadonly<const EepromBackend> back() const { return {backend, offset + allocation - 1}; }

		constexpr Iterator<const ByteAccessReadonly<const EepromBackend>> begin() const { return {backend, offset}; }
		constexpr Iterator<const ByteAccessReadonly<const EepromBackend>> end() const { return {backend, offset + allocation}; }

		constexpr ReverseIterator<const ByteAccessReadonly<const EepromBackend>> rbegin() const
		{
			return {backend, offset + allocation - 1};
		}
		constexpr ReverseIterator<const ByteAccessReadonly<const EepromBackend>> rend() const { return {backend, offset - 1}; }

		constexpr ByteAccessReadonly<const EepromBackend> operator[](const uint16_t address) const { return {backend, address}; }
	};
}
