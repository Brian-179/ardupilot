#include "mode.h"
#include "Plane.h"
//#include "Arduino.h"
//#include <iostream>
//#include <string.h>

#include <AP_HAL/AP_HAL.h>
#include <AP_HAL/AP_HAL_Boards.h>
//#include <AP_HAL/utility/Location.h>
#include <AP_HAL/AP_HAL_Main.h>

//const AP_HAL::HAL &hal = AP_HAL::get_HAL();
static const uint8_t PIN_PD4 = 4; // Define pin PD4

/*
bool ModeTVC::init(bool ignore_checks){
    return true;
}
*/

using namespace std;

void ModeTVC::setup(){
    hal.gpio->pinMode(PIN_PD4, HAL_GPIO_OUTPUT);
    hal.gpio->write(PIN_PD4, false);
    gcs().send_text(MAV_SEVERITY_INFO, "setting up, sweetie");
}

void ModeTVC::update()
{
    static bool ready = false;
    if (ready == false){
        setup();
    }
    plane.nav_roll_cd = 0;
    plane.nav_pitch_cd = 90;
    if ((double)ToDeg(ahrs.get_pitch()) >= 20){
        gcs().send_text(MAV_SEVERITY_INFO, "Calm down, honey");
    } 
    //gcs().send_text(MAV_SEVERITY_INFO, "jeez, honey");
    //gcs().send_text(MAV_SEVERITY_INFO, to_string((double)ToDeg(ahrs.get_pitch())));
}

void ModeTVC::run()
{
    plane.stabilize_roll();
    plane.stabilize_pitch();
    //TVC_stick_mixing_direct();
    plane.stabilize_yaw();

    SRV_Channels::set_output_scaled(SRV_Channel::k_throttle, 0.0);
    SRV_Channels::set_output_scaled(SRV_Channel::k_throttleLeft, 0.0);
    SRV_Channels::set_output_scaled(SRV_Channel::k_throttleRight, 0.0);

    SRV_Channels::set_output_to_trim(SRV_Channel::k_throttle);
    SRV_Channels::set_output_to_trim(SRV_Channel::k_throttleLeft);
    SRV_Channels::set_output_to_trim(SRV_Channel::k_throttleRight);

    //gcs().send_text(MAV_SEVERITY_INFO, "start, honey");

    //output_pilot_throttle();
}

/*
void setup(){

}

void loop(){

}

plane.set_mode(plane.mode_rtl, ModeReason::MISSION_END);

                (double)ToDeg(ahrs.get_roll()),
                (double)ToDeg(ahrs.get_pitch()),
                (double)ToDeg(ahrs.get_yaw()),

void ModeAuto::run()
{
    if (plane.mission.get_current_nav_cmd().id == MAV_CMD_NAV_ALTITUDE_WAIT) {

        wiggle_servos();

        SRV_Channels::set_output_scaled(SRV_Channel::k_throttle, 0.0);
        SRV_Channels::set_output_scaled(SRV_Channel::k_throttleLeft, 0.0);
        SRV_Channels::set_output_scaled(SRV_Channel::k_throttleRight, 0.0);

        SRV_Channels::set_output_to_trim(SRV_Channel::k_throttle);
        SRV_Channels::set_output_to_trim(SRV_Channel::k_throttleLeft);
        SRV_Channels::set_output_to_trim(SRV_Channel::k_throttleRight);

        // Relax attitude control
        reset_controllers();

    } else {
        // Normal flight, run base class
        Mode::run();

    }
}

*/