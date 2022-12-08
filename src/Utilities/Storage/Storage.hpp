#pragma once

#include <stdint.h>

namespace devuino::utilities
{
	/// @brief Storage is a generic frontend for storing a struct in byte-addressable memory
	/// @tparam Structure Struct to store
	/// @tparam StorageBackend Byte-addressable memory backend
	template<typename Structure, typename StorageBackend>
	class Storage
	{
		static_assert(sizeof(Structure) <= StorageBackend::size(), "Size of structure cannot be larger than backend storage");

		mutable Structure data {};
		StorageBackend backend;

	  public:
		/// @brief Storage is a generic frontend for storing a struct in byte-addressable memory. Constructor will load struct from backend
		/// memory. Destructor will save struct to backend memory.
		/// @param StorageBackend Byte-addressable memory backend
		constexpr Storage(StorageBackend backend) : backend {backend} { load(); }
		~Storage() { save(); }

		constexpr operator Structure() const { return data; }
		constexpr const Structure* const operator->() const { return &data; }
		constexpr Structure* operator->() { return &data; }

		constexpr Storage& operator=(const Structure& structure)
		{
			data = structure;
			return *this;
		}

		/// @brief Save struct to backend memory
		constexpr void save()
		{
			char* bytes = reinterpret_cast<char*>(&data);

			auto iterator = backend.begin();
			for (size_t i = 0; i < sizeof(Structure); ++i, ++iterator)
			{
				*iterator = bytes[i];
			}
		};
		/// @brief Load struct from backend memory
		constexpr void load() const
		{
			char* bytes = reinterpret_cast<char*>(&data);

			auto iterator = backend.begin();
			for (size_t i = 0; i < sizeof(Structure); ++i, ++iterator)
			{
				bytes[i] = *iterator;
			}
		}
	};

	/// @brief StorageReadonly is a generic read-only frontend for storing a struct in byte-addressable memory
	/// @tparam Structure Struct to store
	/// @tparam StorageBackend Byte-addressable memory backend
	template<typename Structure, typename StorageBackend>
	class StorageReadonly
	{
		static_assert(sizeof(Structure) <= StorageBackend::size(), "Size of structure cannot be larger than backend storage");

		mutable Structure data {};
		StorageBackend backend;

	  public:
		/// @brief Storage is a generic frontend for storing a struct in byte-addressable memory. Constructor will load struct from backend
		/// memory. Destructor will save struct to backend memory.
		/// @param StorageBackend Byte-addressable memory backend
		constexpr StorageReadonly(StorageBackend backend) : backend {backend} { load(); }

		constexpr operator Structure() const { return data; }
		constexpr const Structure* const operator->() const { return &data; }

		/// @brief Load struct from backend memory
		constexpr void load() const
		{
			char* bytes = reinterpret_cast<char*>(&data);

			auto iterator = backend.begin();
			for (size_t i = 0; i < sizeof(Structure); ++i, ++iterator)
			{
				bytes[i] = *iterator;
			}
		}
	};
}