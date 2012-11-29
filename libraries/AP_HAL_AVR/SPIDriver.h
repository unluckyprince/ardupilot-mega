
#ifndef __AP_HAL_AVR_SPI_DRIVER_H__
#define __AP_HAL_AVR_SPI_DRIVER_H__

#include <AP_HAL.h>
#include "AP_HAL_AVR_Namespace.h"
#include "GPIO.h"
#include "Semaphore.h"

class AP_HAL_AVR::APM1SPIDriver : public AP_HAL::SPIDriver {
public:
    void init(void* machtnichts);
    AP_HAL::SPIDevice* device(int n);
};

class AP_HAL_AVR::APM2SPIDriver : public AP_HAL::SPIDriver {
public:
    void init(void* machtnichts);
    AP_HAL::SPIDevice* device(int n);
};

class AP_HAL_AVR::AVRSPI0Device : public AP_HAL::SPIDevice {
    AVRSPI0Device(AP_HAL_AVR::AVRGPIO *cs_pin) : _cs_pin(cs_pin) {}
    AP_HAL::Semaphore* get_semaphore();
    void set_transer_mode(uint8_t mode);
    void set_freq(uint32_t freq_hz);
    void cs_assert();
    void cs_release();
    uint8_t transfer(uint8_t data);

private:
    static AP_HAL_AVR::AVRSemaphore _semaphore;
    AP_HAL_AVR::AVRGPIO *_cs_pin;
    uint8_t _divider_bits(uint8_t divider);
    void _set_clock_divider_bits(uint8_t b);
};


class AP_HAL_AVR::AVRSPI2Device : public AP_HAL::SPIDevice {
    AVRSPI2Device(AP_HAL_AVR::AVRGPIO *cs_pin) : _cs_pin(cs_pin) {}
    AP_HAL::Semaphore* get_semaphore();
    void set_transer_mode(uint8_t mode);
    void set_freq(uint32_t freq_hz);
    void cs_assert();
    void cs_release();
    uint8_t transfer(uint8_t data);

private:
    static AP_HAL_AVR::AVRSemaphore _semaphore;
    AP_HAL_AVR::AVRGPIO *_cs_pin;
    uint8_t _divider_bits(uint8_t divider);
    void _set_clock_divider_bits(uint8_t b);
};

class AP_HAL_AVR::AVRSPI3Device : public AP_HAL::SPIDevice {
    AVRSPI3Device(AP_HAL_AVR::AVRGPIO *cs_pin) : _cs_pin(cs_pin) {}
    AP_HAL::Semaphore* get_semaphore();
    void set_transer_mode(uint8_t mode);
    void set_freq(uint32_t freq_hz);
    void cs_assert();
    void cs_release();
    uint8_t transfer(uint8_t data);

private:
    static AP_HAL_AVR::AVRSemaphore _semaphore;
    AP_HAL_AVR::AVRGPIO *_cs_pin;
    uint8_t _divider_bits(uint8_t divider);
    void _set_clock_divider_bits(uint8_t b);
};
#endif // __AP_HAL_AVR_SPI_DRIVER_H__

