//
// Created by llzz53 on 2026/1/10.
//


#ifndef LLZJ_ROBOT_PROJECT_VER001_CHASSIS_H
#define LLZJ_ROBOT_PROJECT_VER001_CHASSIS_H
#include "main.h"
#include "stdbool.h"
typedef enum {
    forward_left=1,
    forward,
    forward_right,
    left,
    stop,
    right,
    backward_left,
    backward,
    backward_right,
}chassis_cmd;

typedef struct {
    int8_t x;
    int8_t y;
    int8_t w;
}chassis_speed;

typedef struct {
    chassis_cmd current_cmd;
    chassis_cmd last_cmd;
    uint32_t current_disconnect;
    uint32_t last_disconnect;
    chassis_speed chassis_target_speed;
    uint8_t speed_mode;
}chassis;



void RTOS_Task_Chassis(void *argument);

void chassis_init(void);
void chassis_get_speed(chassis_cmd);
void chassis_cul_speed();
void chassis_set_cmd(uint8_t);












#endif //LLZJ_ROBOT_PROJECT_VER001_CHASSIS_H