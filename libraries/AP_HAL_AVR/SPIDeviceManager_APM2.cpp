
#include <AP_HAL.h>
#include "SPIDriver.h"
#include "SPIDevices.h"
#include "pins_arduino_mega.h"
using namespace AP_HAL_AVR;

extern const AP_HAL::HAL& hal;

void APM2SPIDeviceManager::init(void* machtnichts) {

    AVRDigitalSource* ms5611_cs = new AVRDigitalSource(_BV(1), PG);
    _ms5611 = new AVRSPI0DeviceDriver(ms5611_cs, 0, 0);
    _ms5611->init();

    AVRDigitalSource* mpu6k_cs = new AVRDigitalSource(_BV(0), PB);
    _mpu6k = new AVRSPI0DeviceDriver(mpu6k_cs, 0, 0);
    _mpu6k->init();
    
    AVRDigitalSource* optflow_cs = new AVRDigitalSource(_BV(3), PF);
    _optflow_spi0 = new AVRSPI0DeviceDriver(optflow_cs, 0, 0);
    _optflow_spi0->init();

    AVRDigitalSource* df_cs = new AVRDigitalSource(_BV(6), PA);
    _dataflash = new AVRSPI3DeviceDriver(df_cs, 0, 0);
    _dataflash->init();

    _optflow_spi3 = new AVRSPI3DeviceDriver(optflow_cs, 0, 0);
    _optflow_spi3->init();
}

AP_HAL::SPIDeviceDriver* APM2SPIDeviceManager::device(enum AP_HAL::SPIDevice d) 
{
    switch (d) {
        case AP_HAL::SPIDevice_Dataflash:
            return _dataflash;
        case AP_HAL::SPIDevice_MS5611:
            return _ms5611;
        case AP_HAL::SPIDevice_MPU6000:
            return _mpu6k;
        case AP_HAL::SPIDevice_ADNS3080_SPI0:
            return _optflow_spi0;
        case AP_HAL::SPIDevice_ADNS3080_SPI3:
            return _optflow_spi3;
        default:
            return NULL;
    };
}

