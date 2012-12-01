/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_INERTIALNAV_H__
#define __AP_INERTIALNAV_H__

#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_AHRS.h>
#include <AP_InertialSensor.h>
#include <AP_Baro.h>
#include <Filter.h>

#define AP_INTERTIALNAV_GRAVITY 9.80665
// default time constant for complementary filter's X & Y axis
#define AP_INTERTIALNAV_TC_XY   3.0
// default time constant for complementary filter's Z axis
#define AP_INTERTIALNAV_TC_Z    1.5

/*
 * AP_InertialNav is an attempt to use accelerometers to augment other
 * sensors to improve altitude position hold
 */
class AP_InertialNav
{
public:

    // Constructor
    AP_InertialNav( AP_AHRS* ahrs,
            AP_InertialSensor* ins, AP_Baro* baro, GPS** gps_ptr ) :
        _ahrs(ahrs),
        _ins(ins),
        _baro(baro),
        _gps_ptr(gps_ptr),
        _baro_last_update(0),
        _gps_last_update(0),
        _xy_enabled(false),
        _comp_filter(AP_INTERTIALNAV_TC_XY, AP_INTERTIALNAV_TC_Z)
        {}

    // Initialisation
    void        init() { 
                            set_time_constant_xy(_time_constant_xy);
                            set_time_constant_z(_time_constant_z); 
        }

    // save_params - save all parameters to eeprom
    void        save_params();

    // set time constant - set timeconstant used by complementary filter
    void        set_time_constant_xy( float time_constant_in_seconds );

    // set time constant - set timeconstant used by complementary filter
    void        set_time_constant_z( float time_constant_in_seconds );

    // check_baro - check if new baro readings have arrived and use them
    // to correct vertical accelerometer offsets
    void        check_baro();

    // correct_with_baro - modifies accelerometer offsets using barometer.
    // dt is time since last baro reading
    void        correct_with_baro(float baro_alt, float dt);

    // set_current_position - all internal calculations are recorded as the
    // distances from this point
    void        set_current_position(int32_t lon, int32_t lat);

    // check_gps - check if new gps readings have arrived and use them to
    // correct position estimates
    void        check_gps();

    // correct_with_gps - modifies accelerometer offsets using gps.
    // dt is time since last gps update
    void        correct_with_gps(int32_t lon, int32_t lat, float dt);

    // update - updates velocities and positions using latest info from
    // accelerometers;
    void        update(float dt);

    // altitude_ok, position_ok - true if inertial based altitude and
    // position can be trusted
    bool        altitude_ok() { return true; }
    bool        position_ok();

    // get_altitude - get latest altitude estimate in cm
    float       get_altitude() { return _position.z; }
    void        set_altitude( int32_t new_altitude) {
        _comp_filter.set_3rd_order_z(new_altitude); 
    }

    // get_velocity_z - get latest climb rate (in cm/s)
    float       get_velocity_z() { return _velocity.z; }
    void        set_velocity_z( int32_t new_velocity ) {
        _comp_filter.set_2nd_order_z(new_velocity);
    }

    // get latitude & longitude positions
    int32_t     get_latitude();
    int32_t     get_longitude();

        // get latitude & longitude positions from base location
    float       get_latitude_diff();
    float       get_longitude_diff();
    
    // get velocity in latitude & longitude directions
    float       get_latitude_velocity();
    float       get_longitude_velocity();

    // class level parameters
    static const struct AP_Param::GroupInfo var_info[];

//protected:
    AP_AHRS*        _ahrs;
    AP_InertialSensor*  _ins;
    AP_Baro*        _baro;
    GPS**           _gps_ptr;

    uint32_t        _baro_last_update;
    // system time of last gps update
    uint32_t        _gps_last_update;
    // time of last gps update according to the gps itself
    uint32_t        _gps_last_time;

    bool            _xy_enabled;

    // time constant for complementary filter's horizontal corrections
    AP_Float        _time_constant_xy;
    // time constant for complementary filter's vertical corrections
    AP_Float        _time_constant_z;
    // latest accelerometer values
    Vector3f        _accel_bf;
    // accelerometer values converted from body to earth frame
    Vector3f        _accel_ef;
    // accelerometer corrections calculated by complementary filter
    AP_Vector3f     _accel_correction;
    // latest velocity estimate (integrated from accelerometer values)
    Vector3f        _velocity;
    // latest position estimate
    Vector3f        _position;
    // base latitude
    int32_t         _base_lat;
    // base longitude
    int32_t         _base_lon;
    // conversion of longitude to meters
    float           _lon_to_m_scaling;

    // 3rd order complementary filter for combining baro readings
    // with accelerometers
    ThirdOrderCompFilter   _comp_filter;

};

#endif // __AP_INERTIALNAV_H__
