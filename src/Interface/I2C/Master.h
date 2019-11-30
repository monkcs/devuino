#ifndef I2C_MASTER_H
#define I2C_MASTER_H

/* Include two-wire implementation from arduino code library */
extern "C"
{
    #include "twi.h"
    #include "twi.c"
}

namespace devuino
{
    namespace interface
    {
        namespace I2C {
            class Master
            {
                public:
                    /* This class will use std::array when it is possible to link it in.
                     * Right now there is no way to select different (if present) interfaces. */
                    Master(uint8_t interface) : interface(interface)
                    {
                        twi_init();
                    };

                    ~Master()
                    {
                        /* If the functions is called it may stop other instances?? */
                        // twi_disable();
                    };

                    enum class Status
                    {
                        Success = 0,
                        BufferOverflow = 1,
                        AddressNACK = 2,
                        DataNACK = 3,
                        Other = 4
                    };

                    void address(uint8_t slave)
                    {
                        this->slave = slave;
                    };

                    /* Read data into array specified. Returns number of bytes read */
                    uint8_t read(uint8_t* data, uint8_t lenght, bool stopsign)
                    {
                        return twi_readFrom(slave, data, lenght, stopsign);
                    };
 
                    Status send(uint8_t* data, uint8_t lenght, bool asynchronous, bool stopsign)
                    {
                        return (Status)twi_writeTo(slave, data, lenght, asynchronous, stopsign);
                    };

                    void speed(uint32_t frequency)
                    {
                        twi_setFrequency(frequency);
                    };

                protected:
                    const uint8_t interface;
                    uint8_t slave;
            };
        }
    }
}

#endif
