
#include <AP_HAL.h>
#include "SPIDriver.h"
#include "SPIDevices.h"
#include "GPIO.h"
#include "pins_arduino_mega.h"
using namespace AP_HAL_AVR;

extern const AP_HAL::HAL& hal;

void APM1SPIDeviceManager::init(void* machtnichts) {
    AVRDigitalSource* df_cs = new AVRDigitalSource(_BV(0), PB);
    _dataflash = new AVRSPI0DeviceDriver(df_cs, 0, 0);
    _dataflash->init();

    AVRDigitalSource* opt_cs = new AVRDigitalSource(_BV(3), PC);
    _optflow = new AVRSPI0DeviceDriver(opt_cs, 0/* XXX clock div by 8 */, 0);
    _optflow->init();

    AVRDigitalSource* adc_cs = new AVRDigitalSource(_BV(4), PC);
    _adc = new AVRSPI2DeviceDriver(adc_cs, 0, 2);
    _adc->init();
}

AP_HAL::SPIDeviceDriver* APM1SPIDeviceManager::device(enum AP_HAL::SPIDevice d) 
{
    switch (d) {
        case AP_HAL::SPIDevice_Dataflash:
            return _dataflash;
        case AP_HAL::SPIDevice_ADS7844:
            return _adc;
        case AP_HAL::SPIDevice_ADNS3080_SPI0:
            return _optflow;
        default:
            return NULL;
    };
}

