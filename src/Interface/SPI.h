#ifndef SPI_H
#define SPI_H

#include <SPI.h>

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

            template <typename T>
            class Master
            {
              public:
                friend class Spi;

                constexpr void initiate(const uint32_t clockspeed = 4000000,
                              const devuino::interface::spi::Bitorder order = devuino::interface::spi::Bitorder::MSB,
                              const devuino::interface::spi::Mode mode = devuino::interface::spi::Mode::SPI0)
                {
                    this->configuration = SPISettings(clockspeed, (uint8_t)order, (uint8_t)mode);
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

                void transfer(void* buffer, const size_t lenght) const
                {
                    start();
                    SPI.transfer(buffer, lenght);
                    stop();
                };

              private:
                const T chipselect;
                SPISettings configuration;

                Master(const T chipselect) : chipselect(chipselect)
                {
                    this->chipselect.initiate(pin::Mode::OutputDigital);
                    chipselect.digitalwrite(true);
                };

                void start() const
                {
                    SPI.beginTransaction(configuration);
                    chipselect.digitalwrite(false);
                };

                void stop() const
                {
                    chipselect.digitalwrite(true);
                    SPI.endTransaction();
                };
            };

            class Spi final
            {
              public:
                Spi(const uint8_t interface)
                {
                    SPI.begin();
                };
                ~Spi()
                {
                    SPI.end();
                };

                template <typename T> Master<T> constexpr master(const T chipselect) const
                {
                    return Master<T>(chipselect);
                };
            };
        }
    }
}

#endif
