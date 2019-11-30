#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

/* Include two-wire implementation from arduino code library */
#include <Wire.h>

namespace devuino
{
    namespace interface
    {
        namespace I2C {
            class Slave
            {
                public:
                    Slave(uint8_t interface) : interface(interface)
                {
                    twi_init(void);
                };

                    ~Slave()
                    {
                        /* If the functions is called it may stop other instances?? */
                        // twi_disable();
                    };

                    /* Set address for this device */
                    void address(uint8_t device)
                    {
                        twi_setAddress(device);
                    };

                    class final
                    {
                        public:
                            Status message(const uint8_t[] data, uint8_t lenght)
                            {
                                return (TransmitStatus)twi_transmit(data, lenght);
                            };

                            void recive(void (*function)(uint8_t*, int))
                            {
                                twi_attachSlaveRxEvent(function);
                            };

                            void transmit(void (*function)(void)) 
                            {
                                twi_attachSlaveTxEvent(function);
                            };

                            enum class Status
                            {
                                Success = 0,
                                BufferOwerflow = 1,
                                NotSlave = 2
                            };
                    } callback;

                protected:
                    const uint8_t interface;
            };
        }
    }
}

#endif
