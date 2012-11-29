

#include <avr/io.h>

#include <AP_HAL.h>
#include "SPIDriver.h"
#include "GPIO.h"
using namespace AP_HAL_AVR;

extern const AP_HAL::HAL& hal;

AP_HAL_AVR::AVRSemaphore AVRSPI2Device::_semaphore;

AP_HAL::Semaphore* AVRSPI2Device::get_semaphore() {
    return &_semaphore;
}

void AVRSPI2Device::set_transfer_mode(uint8_t mode) {

}

void AVRSPI2Device::set_freq(uint32_t freq_hz) {

}

void AVRSPI2Device::cs_assert() {
    _cs_pin->write(0);
}

void AVRSPI2Device::cs_release() {
    _cs_pin->write(1);
}

uint8_t AVRSPI2Device::transfer(uint8_t data) {

}

uint8_t AVRSPI2Device::_divider_bits(uint8_t div) {

}

void AVRSPI2Device::_set_clock_divider_bits(uint8_t b) {

}
