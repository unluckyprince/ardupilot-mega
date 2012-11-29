
#include <avr/io.h>
#include "utility/pins_arduino_mega.h"

#include <AP_HAL.h>
#include "SPIDriver.h"
using namespace AP_HAL_AVR;

extern const AP_HAL::HAL& hal;

void APM1SPIDriver::init(void* machtnichts) {
    hal.gpio->pinMode(SCK, GPIO_OUTPUT);
    hal.gpio->pinMode(MOSI, GPIO_OUTPUT);
    hal.gpio->pinMode(SS, GPIO_OUTPUT);

    hal.gpio->write(SCK, 0);
    hal.gpio->write(MOSI,0);
    hal.gpio->write(SS,  0);

//    SPCR |= _BV(MSTR);
//    SPCR |= _BV(SPE);
//    set_freq( 1000000);
}



