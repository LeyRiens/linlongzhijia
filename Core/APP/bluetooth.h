//
// Created by llzz53 on 2026/1/10.
//

#ifndef LLZJ_ROBOT_PROJECT_VER001_BLE_H
#define LLZJ_ROBOT_PROJECT_VER001_BLE_H
#include <main.h>
#define BUFFER_SIZE 16
#define COMMAND_SIZE 4



uint8_t get_cmd_head();
uint8_t get_cmd_size();
uint8_t get_cmd_type();
uint8_t get_cmd();



void bluetooth_init();
void bluetooth_receive_start();



#endif //LLZJ_ROBOT_PROJECT_VER001_BLE_H