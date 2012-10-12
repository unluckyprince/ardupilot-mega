/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_INERTIAL_SENSOR_STUB_H__
#define __AP_INERTIAL_SENSOR_STUB_H__

#include "AP_InertialSensor.h"

class AP_InertialSensor_Stub : public AP_InertialSensor
{
public:

    AP_InertialSensor_Stub() {
    }

    /* Concrete implementation of AP_InertialSensor functions: */
    uint16_t        init();
    bool            update();
    bool            new_data_available();
    float           gx();
    float           gy();
    float           gz();
    float           ax();
    float           ay();
    float           az();
    float           temperature();
    uint32_t        get_delta_time_micros();
    uint32_t        get_last_sample_time_micros();
    float           get_gyro_drift_rate();
    uint16_t        num_samples_available();

protected:
    uint16_t        _init_sensor();
};

#endif // __AP_INERTIAL_SENSOR_STUB_H__
