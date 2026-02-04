//
// Created by llzz53 on 2026/1/10.
//
#include "cmsis_os2.h"
#include <main.h>
#include "../APP/motor_chassis.h"
#include "chassis.h"
#include "FreeRTOS.h"
#include "task.h"
#include "../APP/pid.h"


#define DISCONNECT_TIMEOUT 1000

#define RADIUS 3
#define WHEEL_TRACK 3
#define WHEEL_BASE 3

#define TARGET_SPEED_FAST 3
#define TARGET_SPEED_SLOW 3

#define MOTOR_FRONT_LEFT 0
#define MOTOR_BACK_LEFT 1
#define MOTOR_BACK_RIGHT 2
#define MOTOR_FRONT_RIGHT 3

#define SPEED_0 0




chassis chassis_state;


void RTOS_Task_Chassis(void *argument) {
    chassis_init();
    for(;;)
    {
        chassis_get_speed(chassis_state.current_cmd);
        chassis_cul_speed();
        pid_cal();
        motor_output_update();
        osDelay(10);
    }
}


void chassis_init(void)
{
    chassis_state.current_cmd = stop;
    chassis_state.last_cmd = stop;
    chassis_state.current_disconnect = 0;
    chassis_state.last_disconnect = 0;
    chassis_state.speed_mode= TARGET_SPEED_SLOW;
    chassis_state.chassis_target_speed.x=0;
    chassis_state.chassis_target_speed.y=0;
    chassis_state.chassis_target_speed.w=0;
}


void chassis_get_speed(chassis_cmd cmd) {
    chassis_state.chassis_target_speed.x = motor_get_speed_x(cmd);
    chassis_state.chassis_target_speed.y = motor_get_speed_y(cmd);
}


void chassis_cul_speed() {
    float _0 = -chassis_state.chassis_target_speed.x + chassis_state.chassis_target_speed.y + chassis_state.chassis_target_speed.w * (WHEEL_TRACK + WHEEL_BASE) / 2;
    float _1 = -chassis_state.chassis_target_speed.x- chassis_state.chassis_target_speed.y + chassis_state.chassis_target_speed.w * (WHEEL_TRACK + WHEEL_BASE) / 2;
    float _2 = chassis_state.chassis_target_speed.x - chassis_state.chassis_target_speed.y + chassis_state.chassis_target_speed.w * (WHEEL_TRACK + WHEEL_BASE) / 2;
    float _3 = chassis_state.chassis_target_speed.x +chassis_state.chassis_target_speed.y + chassis_state.chassis_target_speed.w * (WHEEL_TRACK + WHEEL_BASE) / 2;
    motor_target_output_set(_0*chassis_state.speed_mode,MOTOR_FRONT_LEFT);
    motor_target_output_set(_1*chassis_state.speed_mode,MOTOR_BACK_LEFT);
    motor_target_output_set(_2*chassis_state.speed_mode,MOTOR_BACK_RIGHT);
    motor_target_output_set(_3*chassis_state.speed_mode,MOTOR_FRONT_RIGHT);
    motor_set_direction();
}


void chassis_set_cmd(uint8_t cmd) {
    chassis_state.current_cmd= cmd;
}

