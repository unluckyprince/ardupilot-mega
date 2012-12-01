// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

/// @file	AP_Camera.h
/// @brief	Photo or video camera manager, with EEPROM-backed storage of
///         constants.
/// @author Amilcar Lucas

#ifndef __AP_CAMERA_H__
#define __AP_CAMERA_H__

#include <AP_Param.h>
#include <GCS_MAVLink.h>

/// @class	Camera
/// @brief	Object managing a Photo or video camera
class AP_Camera {

public:
    /// Constructor
    ///
    AP_Camera() :
        // waypoint trigger variable
        picture_time(0),
        wp_distance_min(10),
        keep_cam_trigg_active_cycles(0),
        // timer variable for throttle_pic
        thr_pic(0),
        // PK6 chosen as it not near anything so safer for soldering
        camtrig(83)
    {
    }

    // single entry point to take pictures
    void            trigger_pic();

    // de-activate the trigger after some delay, but without using a delay()
    // function
    void            trigger_pic_cleanup();

    // MAVLink methods
    void            configure_msg(mavlink_message_t* msg);
    void            control_msg(mavlink_message_t* msg);

    // waypoint trigger variable
    int16_t         picture_time;
    // take picture if distance to WP is smaller than this
    int32_t         wp_distance_min;

    static const struct AP_Param::GroupInfo        var_info[];

private:
    // event loop cycles to keep trigger active
    uint8_t         keep_cam_trigg_active_cycles;
    // timer variable for throttle_pic
    int16_t         thr_pic;
    // PK6 chosen as it not near anything so safer for soldering
    int16_t         camtrig;

    // 0=Servo, 1=relay, 2=throttle_off time,
    // 3=throttle_off waypoint, 4=transistor
    AP_Int8         trigger_type;

    // Servo operated camera
    void            servo_pic();
    // basic relay activation
    void            relay_pic();
    // pictures blurry? use this trigger.
    // Turns off the throttle until for # of cycles of medium loop then
    // takes the picture and re-enables the throttle.
    void            throttle_pic();
    // pictures blurry? use this trigger. Turns off the throttle until
    // closer to waypoint then takes the picture and re-enables the throttle.
    void            distance_pic();
    // hacked the circuit to run a transistor? use this trigger to send output.
    void            NPN_pic();

};

#endif /* AP_CAMERA_H */
