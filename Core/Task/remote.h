//
// Created by llzz53 on 2026/1/10.
//

#ifndef LLZJ_ROBOT_PROJECT_VER001_REMOTE_H
#define LLZJ_ROBOT_PROJECT_VER001_REMOTE_H

#define COMMAND_HEAD 0xAA

void RTOS_Task_Remote(void *argument);

typedef enum {
    NO_CMD=0,
    CHASSIS_CMD,
    GIMBAL_CMD,
    ARM_CMD,
    VISION_CMD
}cmd_type;

void distribute_cmd();

cmd_type remote_get_cmd();

#endif //LLZJ_ROBOT_PROJECT_VER001_REMOTE_H