#pragma once

#include <SPI.h>
#include <stdint.h>

namespace devuino
{
	namespace interface
	{
		namespace spi
		{
			enum class Bitorder : uint8_t
			{
				MSB = 1,
				LSB = 0
			};

			enum class Mode : uint8_t
			{
				SPI0 = SPI_MODE0,
				SPI1 = SPI_MODE1,
				SPI2 = SPI_MODE2,
				SPI3 = SPI_MODE3
			};

			template<typename Type>
			class Controller
			{
			  public:
				friend class Spi;

				void initiate(const uint32_t clockspeed = 4000000, const Bitorder order = Bitorder::MSB, const Mode mode = Mode::SPI0)
				{
					this->configuration = SPISettings(clockspeed, static_cast<uint8_t>(order), static_cast<uint8_t>(mode));
				};

				uint8_t transfer(const uint8_t data) const
				{
					start();
					const auto result = SPI.transfer(data);
					stop();

					return result;
				};

				uint8_t transfer(const uint8_t address, const uint8_t data) const
				{
					start();
					SPI.transfer(address);
					const auto result = SPI.transfer(data);
					stop();

					return result;
				};

				uint16_t transfer16(const uint16_t data) const
				{
					start();
					const auto result = SPI.transfer16(data);
					stop();

					return result;
				};

				template<size_t N>
				void transfer(const uint8_t buffer[N]) const
				{
					start();
					SPI.transfer((void*)(buffer), N);
					stop();
				};

			  private:
				Type chipselect;
				SPISettings configuration;

				Controller(const Type chipselect) : chipselect {chipselect}
				{
					this->chipselect.initiate(pin::Output::Digital);
					chipselect.digital(true);
				};

				void start() const
				{
					SPI.beginTransaction(configuration);
					chipselect.digital(false);
				};

				void stop() const
				{
					chipselect.digital(true);
					SPI.endTransaction();
				};
			};

			class Spi
			{
			  public:
				Spi(const uint8_t interface) { SPI.begin(); };

				~Spi() { SPI.end(); };

				template<typename Type>
				Controller<Type> controller(const Type chipselect) const
				{
					return Controller<Type> {chipselect};
				};
			};
		}
	}
}
