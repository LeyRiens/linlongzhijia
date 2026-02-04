//
// Created by llzz53 on 2026/1/19.
//

#include "vision.h"

#include "cmsis_os2.h"
#include "../APP/raser.h"

static bool vision_on;

void RTOS_Task_Vision(void *argument) {
    raser_off();
    vision_on=false;
    for (;;) {
    ///////////尚未实现/////////

        /*
         *设置为最高优先级
         *开启管道接收，无限期挂起等待
         *接收像素差
         *调动云台
         *调动机械臂

         */
        osDelay(10);
    }
}

void vision_task_on() {
    raser_off();
    vision_on=true;
}