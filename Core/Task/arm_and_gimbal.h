//
// Created by llzz53 on 2026/1/11.
//

#ifndef LLZJ_ROBOT_PROJECT_VER001_MACH_ARM_H
#define LLZJ_ROBOT_PROJECT_VER001_MACH_ARM_H
#include <main.h>

typedef enum {
    ROBOT_ARM_UP=0,
    ROBOT_ARM_LOW,
    ROBOT_ARM_STORAGE,
    ROBOT_ARM_GET_STORAGE,
    ROBOT_ARM_EXCHANGE,
    ROBOT_ARM_VISION,
    ROBOT_PAW_GRIP,
    ROBOT_PAW_RELEASE,
    ROBOT_GIMBAL_TURN
}robot_arm_motion;

typedef enum {
    CMD_ARM_READY=0x00,
    CMD_ARM_UP,
    CMD_ARM_LOW,
    CMD_ARM_VISION,
    CMD_ARM_STORAGE,
    CMD_ARM_EXCHANGE,
}robot_arm_cmd;

typedef struct {
    robot_arm_motion queue[16];
    uint8_t index;
    uint8_t size;
}robot_arm_motion_queue;

void robot_arm_set_cmd(uint8_t cmd);
robot_arm_cmd robot_arm_get_cmd();

void robot_arm_distribute_cmd();

void robot_arm_queue_update();

void robot_arm_queue_init();

void robot_arm_queue_add(robot_arm_motion,uint8_t);

void robot_arm_init();

void robot_arm_up();

void robot_arm_low();

void robot_arm_vision();

void robot_arm_storage();

void robot_arm_exchange();

int get_storage_count();

void reset_storage_count();




#endif //LLZJ_ROBOT_PROJECT_VER001_MACH_ARM_H