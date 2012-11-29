
#ifndef __AP_HAL_SPI_DRIVER_H__
#define __AP_HAL_SPI_DRIVER_H__

#include "AP_HAL_Namespace.h"

/**
 * A simple SPIDriver interface directly copied from Arduino SPI driver.
 * This will not be the final AP_HAL interface.
 * We will need an abstraction for selecting slave devices and performing bulk
 * transfers to be portable to other platforms.
 */

#define SPI_DRIVER_TRANSFER_MODE_FOO 0
#define SPI_DRIVER_TRANSFER_MODE_BAR 1

class AP_HAL::SPIDriver {
public:
    SPIDriver() {}
    virtual void init(void *) = 0;
    virtual SPIDevice* device(int n) = 0;
};

class AP_HAL::SPIDevice {
    virtual AP_HAL::Semaphore* get_semaphore() = 0;
    virtual void set_transfer_mode(uint8_t mode) = 0;
    virtual void set_freq(uint32_t freq_hz) = 0;
    virtual void cs_assert();
    virtual void cs_release();
    virtual uint8_t transfer (uint8_t data) = 0;
};

#endif // __AP_HAL_SPI_DRIVER_H__

