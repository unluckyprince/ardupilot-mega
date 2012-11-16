/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include "AP_InertialSensor_Stub.h"

uint16_t AP_InertialSensor_Stub::_init_sensor() {
    return AP_PRODUCT_ID_NONE;
}

/*================ AP_INERTIALSENSOR PUBLIC INTERFACE ==================== */

bool AP_InertialSensor_Stub::update( void ) {
    return true;
}
bool AP_InertialSensor_Stub::new_data_available( void ) {
    return true;
}


float AP_InertialSensor_Stub::gx() {
    return 0.0f;
}
float AP_InertialSensor_Stub::gy() {
    return 0.0f;
}
float AP_InertialSensor_Stub::gz() {
    return 0.0f;
}

float AP_InertialSensor_Stub::ax() {
    return 0.0f;
}
float AP_InertialSensor_Stub::ay() {
    return 0.0f;
}
float AP_InertialSensor_Stub::az() {
    return 0.0f;
}

float AP_InertialSensor_Stub::temperature() {
    return 0.0;
}
uint32_t AP_InertialSensor_Stub::get_delta_time_micros() {
    return 0;
}
uint32_t AP_InertialSensor_Stub::get_last_sample_time_micros() {
    return 0;
}
float AP_InertialSensor_Stub::get_gyro_drift_rate(void) {
    return 0.0;
}
uint16_t AP_InertialSensor_Stub::num_samples_available()
{
    return 1;
}
