

#include <avr/io.h>

#include <AP_HAL.h>
#include "SPIDevices.h"
#include "GPIO.h"
#include "Semaphore.h"

#include "pins_arduino_mega.h"

using namespace AP_HAL_AVR;

#define SPI3_MOSI 14
#define SPI3_MISO 15

extern const AP_HAL::HAL& hal;

AVRSemaphore AVRSPI3DeviceDriver::_semaphore;

void AVRSPI3DeviceDriver::init() {
    /* the spi3 (USART3) sck pin PORTJ2 is not enumerated
     * by the arduino pin numbers, so we access it directly
     * with AVRDigitalSource. */
    AVRDigitalSource spi3_sck(_BV(2), PJ);
    spi3_sck.mode(GPIO_OUTPUT);
    hal.gpio->pinMode(SPI3_MOSI, GPIO_OUTPUT);
    hal.gpio->pinMode(SPI3_MISO, GPIO_INPUT);

    /* UMSELn1 and UMSELn2: USART in SPI Master mode */
    UCSR3C = _BV(UMSEL31) | _BV(UMSEL30);
    /* Enable RX and TX. */
    UCSR3B = _BV(RXEN3) | _BV(TXEN3);

    /* Setup chip select pin */
    _cs_pin->mode(GPIO_OUTPUT);
    _cs_pin->write(1);
}

AP_HAL::Semaphore* AVRSPI3DeviceDriver::get_semaphore() {
    return &_semaphore;
}

void AVRSPI3DeviceDriver::cs_assert() {
    /* set the device UCSRnC configuration bits.
     * only sets data order, clock phase, and clock polarity bits (lowest
     * three bits)  */
    const uint8_t new_ucsr3c = UCSR3C | (_ucsr3c & (0x07));
    UCSR3C = new_ucsr3c;
    /* set the device baud rate */
    UBRR3 = _ubrr3;

    _cs_pin->write(0);
}

void AVRSPI3DeviceDriver::cs_release() {
    _cs_pin->write(1);
}

uint8_t AVRSPI3DeviceDriver::transfer(uint8_t data) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR3A & _BV(UDRE3)) ) ;

    /* Put data into buffer, sends the data */
    UDR3 = data;

    /* Wait for data to be received */
    while ( !(UCSR3A & _BV(RXC3)) ) ;

    /* Get and return received data from buffer */
    return UDR3;
}

