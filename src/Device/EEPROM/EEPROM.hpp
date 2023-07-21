#pragma once

#include "../../Utilities/Move/Move.hpp"
#include "../../Utilities/Storage/Storage.hpp"
#include "Allocation.hpp"

#include <stdint.h>

namespace devuino::device
{
	/// @brief EEPROM is a generic device to access its memory both in raw or managed mode
	/// @tparam EepromBackend Physical or logical backend
	template<typename EepromBackend>
	class EEPROM
	{
		static_assert(EepromBackend::lenght > 0, "Storage size of EEPROM needs to be larger than zero");
		static_assert(EepromBackend::lenght <= 65535, "Current implementation cannot handle larger storage size than 65535 bytes");

		mutable EepromBackend backend;

	  public:
		constexpr EEPROM(EepromBackend&& backend) : backend {devuino::move(backend)} { }

		/// @brief Allocation of raw EEPROM storage
		/// @tparam allocation Size of allocation in bytes
		/// @tparam offset Offset from begining of EEPROM storage in bytes
		template<int allocation = EepromBackend::lenght, int offset = 0>
		constexpr auto raw()
		{
			return Allocation<EepromBackend, allocation, offset> {backend};
		}

		/// @brief Allocation of raw const EEPROM storage
		/// @tparam allocation Size of allocation in bytes
		/// @tparam offset Offset from begining of EEPROM storage in bytes
		template<int allocation = EepromBackend::lenght, int offset = 0>
		constexpr auto raw() const
		{
			return AllocationReadonly<const EepromBackend, allocation, offset> {backend};
		}

		/// @brief Allocate a struct of EEPROM storage
		/// @tparam Structure Struct to allocate
		/// @tparam offset Offset from begining of EEPROM storage in bytes
		template<typename Structure, int offset = 0>
		constexpr auto managed()
		{
			return Storage<Structure, Allocation<EepromBackend, sizeof(Structure), offset>> {backend};
		}

		/// @brief Allocate a const struct of EEPROM storage
		/// @tparam Structure Struct to allocate
		/// @tparam offset Offset from begining of EEPROM storage in bytes
		template<typename Structure, int offset = 0>
		constexpr auto managed() const
		{
			return StorageReadonly<Structure, const Allocation<EepromBackend, sizeof(Structure), offset>> {backend};
		}
	};
}
