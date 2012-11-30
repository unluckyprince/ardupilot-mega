
#include <avr/io.h>

#include <AP_HAL.h>
#include "SPIDevices.h"
#include "GPIO.h"
#include "Semaphore.h"
#include "pins_arduino_mega.h"
using namespace AP_HAL_AVR;

extern const AP_HAL::HAL& hal;

#define SPI0_MISO_PIN 50
#define SPI0_MOSI_PIN 51
#define SPI0_SCK_PIN  52

AVRSemaphore AVRSPI0DeviceDriver::_semaphore;

void AVRSPI0DeviceDriver::init() {
    hal.gpio->pinMode(SPI0_MISO_PIN, GPIO_INPUT);
    hal.gpio->pinMode(SPI0_MOSI_PIN, GPIO_OUTPUT);
    hal.gpio->pinMode(SPI0_SCK_PIN, GPIO_OUTPUT);

    _cs_pin->mode(GPIO_OUTPUT);
    _cs_pin->write(1);
}

AP_HAL::Semaphore* AVRSPI0DeviceDriver::get_semaphore() {
    return &_semaphore;
}

void AVRSPI0DeviceDriver::cs_assert() {
    uint8_t new_spcr = SPCR | (_spcr & (CPOL | CPHA | SPR1 | SPR0));
    SPCR = new_spcr;  
    uint8_t new_spsr = SPSR | (_spsr & (SPI2X));
    SPSR = new_spsr;
    _cs_pin->write(0);
}

void AVRSPI0DeviceDriver::cs_release() {
    _cs_pin->write(1);
}

uint8_t AVRSPI0DeviceDriver::transfer(uint8_t data) {
    SPDR = data;
    while(!(SPSR & _BV(SPIF)));
    return SPDR;
}

