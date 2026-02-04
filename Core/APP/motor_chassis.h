//
// Created by llzz53 on 2026/1/19.
//

#ifndef LLZJ_ROBOT_PROJECT_VER001_MOTOR_MECANUM_H
#define LLZJ_ROBOT_PROJECT_VER001_MOTOR_MECANUM_H
#include <stdint.h>

typedef enum {
    MOTOR_FORWARD_LEFT=1,
    MOTOR_FORWARD,
    MOTOR_FORWARD_RIGHT,
    MOTOR_LEFT,
    MOTOR_STOP,
    MOTOR_RIGHT,
    MOTOR_BACKWARD_LEFT,
    MOTOR_BACKWARD,
    MOTOR_BACKWARD_RIGHT,
}motor_direction;

typedef enum {
    SPIN_STOP=0,
    SPIN_LEFT,
    SPIN_RIGHT
}motor_spin;


void motor_output_update();

int8_t motor_get_speed_x(uint8_t);
int8_t motor_get_speed_y(uint8_t);

void motor_set_direction();


float motor_get_target_speed(uint8_t);
float motor_get_current_speed(uint8_t);

void motor_stop();

void motor_target_output_set(float,uint8_t);
void motor_final_output_set(uint16_t,uint8_t);
#endif //LLZJ_ROBOT_PROJECT_VER001_MOTOR_MECANUM_H