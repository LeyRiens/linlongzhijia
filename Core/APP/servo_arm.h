//
// Created by llzz53 on 2026/1/14.
//

#ifndef LLZJ_ROBOT_PROJECT_VER001_SERVO_H
#define LLZJ_ROBOT_PROJECT_VER001_SERVO_H
#include "main.h"
#define TRAJ_SIZE 100
#define SERVO_COUNT 3

#define ARM_DIRECTION_NEGATIVE -1
#define ARM_DIRECTION_POSITIVE 1

#define ARM_END_POSITIVE
#define ARM_END_NEGATIVE
//机械臂位置，用于确定轨迹正逆向
typedef enum {
    UP=0x00,
    LOW,
    STORAGE,
    GET_STORAGE,
    EXCHANGE,
    VISION,
}arm_position;


typedef enum {
    ARM_READY=0,
    ARM_RUNNING
}arm_state;


typedef struct {
    arm_position current_position;
    const uint8_t (*traj)[SERVO_COUNT][TRAJ_SIZE];
    arm_state state;
    int8_t index;
    int8_t direction;
}servo_action;


void servo_arm_init();



void servo_set_traj(arm_position);
void servo_arm_traj_update();



void servo_arm_set_state(arm_state);
arm_state servo_arm_get_state();




#endif //LLZJ_ROBOT_PROJECT_VER001_SERVO_H
