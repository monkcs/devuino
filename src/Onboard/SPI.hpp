#pragma once

#include "../Device/Switch/Switch.hpp"
#include "Digital.hpp"

#include <SPI.h>
#include <stdint.h>

namespace devuino::onboard::spi
{
	template<typename DigitalBackend>
	class Transaction
	{
		devuino::device::Switch<DigitalBackend>& chipselect;
		const SPISettings& configuration;

		Transaction(devuino::device::Switch<DigitalBackend>& chipselect, const SPISettings& configuration) :
			chipselect {chipselect}, configuration {configuration}
		{
			SPI.beginTransaction(configuration);
		}

	  public:
		template<typename T>
		friend class Controller;

		~Transaction() { SPI.endTransaction(); }

		uint8_t transfer(const uint8_t data)
		{
			chipselect.off();
			const auto result = SPI.transfer(data);
			chipselect.on();

			return result;
		}

		uint8_t transfer(const uint8_t address, const uint8_t data)
		{
			chipselect.off();
			SPI.transfer(address);
			const auto result = SPI.transfer(data);
			chipselect.on();

			return result;
		}

		uint16_t transfer16(const uint16_t data)
		{
			chipselect.off();
			const auto result = SPI.transfer16(data);
			chipselect.on();

			return result;
		}

		template<size_t N>
		void transfer(const uint8_t buffer[N])
		{
			chipselect.off();
			SPI.transfer((void*)(buffer), N);
			chipselect.on();
		}
	};

	template<typename DigitalBackend>
	class Controller
	{
		devuino::device::Switch<DigitalBackend> chipselect;
		SPISettings configuration;

		Controller(const DigitalBackend chipselect, SPISettings configuration) :
			chipselect {chipselect, true}, configuration {configuration} {};

	  public:
		friend class Spi;

		Transaction<DigitalBackend> transaction() { return {chipselect, configuration}; }
	};

	class Spi
	{
	  public:
		enum class Bitorder
		{
			MSB = 1,
			LSB = 0
		};

		enum class Mode
		{
			SPI0 = SPI_MODE0,
			SPI1 = SPI_MODE1,
			SPI2 = SPI_MODE2,
			SPI3 = SPI_MODE3
		};

		Spi(const uint8_t interface) { SPI.begin(); }
		~Spi() { SPI.end(); }

		template<typename DigitalBackend = devuino::onboard::DigitalOutput>
		Controller<DigitalBackend> controller(const DigitalBackend chipselect,
											  const uint32_t clockspeed = 4000000,
											  const Bitorder order = Bitorder::MSB,
											  const Mode mode = Mode::SPI0)
		{
			return Controller<DigitalBackend> {chipselect, {clockspeed, static_cast<uint8_t>(order), static_cast<uint8_t>(mode)}};
		}
	};
}