//
// Created by llzz53 on 2026/1/11.
//

#include "arm_and_gimbal.h"
#include "../APP/servo_arm.h"
#include "main.h"
#include "../APP/servo_paw.h"
#include "cmsis_os2.h"


robot_arm_cmd robot_arm_command;
robot_arm_motion_queue robot_arm_queue;
uint8_t  storage_count;



void RTOS_Task_Arm(void *argument) {
    robot_arm_init();
    for (;;) {
       if (robot_arm_command!=CMD_ARM_READY) {
           robot_arm_distribute_cmd();

           servo_arm_traj_update();

           servo_paw_update();

           robot_arm_queue_update();
       }
        osDelay(10);
    }
}


void robot_arm_set_cmd(uint8_t cmd) {
    robot_arm_command=cmd;
}


robot_arm_cmd robot_arm_get_cmd() {
    return robot_arm_command;
}


void robot_arm_distribute_cmd() {
    switch (robot_arm_command) {
        case CMD_ARM_UP:
            robot_arm_up();
            break;
        case CMD_ARM_LOW:
            robot_arm_low();
            break;
        case CMD_ARM_VISION:
            robot_arm_vision();
            break;
        case CMD_ARM_STORAGE:
            robot_arm_storage();
            break;
        case CMD_ARM_EXCHANGE:
            robot_arm_exchange();
            break;
        default:
            break;
    }
}


void robot_arm_queue_update() {
    if (servo_arm_get_state()==ARM_READY&&servo_paw_get_state()==PAW_READY) {
        if (robot_arm_queue.index<robot_arm_queue.size) {
            robot_arm_queue.index++;
        }else {
            robot_arm_command=CMD_ARM_READY;
        }
    }
}



void robot_arm_queue_init() {
    robot_arm_queue.index=0;
    robot_arm_queue.size=0;
}


void robot_arm_queue_add(robot_arm_motion motion, uint8_t index) {
        robot_arm_queue.queue[index]=motion;
    }


void robot_arm_init() {
    servo_arm_init();
    servo_paw_init();

    robot_arm_queue_init();

    robot_arm_command=CMD_ARM_READY;

    reset_storage_count() ;
};


void robot_arm_up() {
    robot_arm_queue_add(ROBOT_ARM_UP,0);
    robot_arm_queue.index=1;
}


void robot_arm_low() {
    robot_arm_queue_add(ROBOT_ARM_UP,0);
    robot_arm_queue_add(ROBOT_ARM_LOW,1);
    robot_arm_queue.index=2;
}


void robot_arm_vision() {
    robot_arm_queue_add(ROBOT_ARM_UP,0);
    robot_arm_queue_add(ROBOT_ARM_VISION,1);
    robot_arm_queue.index=2;
}


void robot_arm_storage() {
        if (get_storage_count()==2) {
            robot_arm_queue_add(ROBOT_ARM_UP,0);
            robot_arm_queue_add(ROBOT_PAW_GRIP,1);
            robot_arm_queue_add(ROBOT_ARM_STORAGE,2);
            robot_arm_queue_add(ROBOT_PAW_RELEASE,3);
            robot_arm_queue_add(ROBOT_ARM_UP,4);
            robot_arm_queue.index=5;
        }else{
            robot_arm_queue_add(ROBOT_ARM_UP,0);
            robot_arm_queue_add(ROBOT_PAW_GRIP,1);
            robot_arm_queue_add(ROBOT_ARM_LOW,2);
            robot_arm_queue.index=3;

        }
    storage_count++;
}


void robot_arm_exchange() {
        uint8_t index=0;
    //switch有意的直接穿透下去
    switch(get_storage_count()) {
        case 3:
            robot_arm_queue_add(ROBOT_ARM_UP,index++);
            robot_arm_queue_add(ROBOT_ARM_EXCHANGE,index++);
            robot_arm_queue_add(ROBOT_PAW_RELEASE,index++);
            robot_arm_queue_add(ROBOT_ARM_UP,index++);
            robot_arm_queue.index=4;
        case 2:
            robot_arm_queue_add(ROBOT_ARM_GET_STORAGE,index++);
            robot_arm_queue_add(ROBOT_PAW_GRIP,index++);
            robot_arm_queue_add(ROBOT_ARM_UP,index++);
            robot_arm_queue_add(ROBOT_ARM_EXCHANGE,index++);
            robot_arm_queue_add(ROBOT_PAW_RELEASE,index++);
            robot_arm_queue_add(ROBOT_ARM_UP,index++);
            robot_arm_queue.index+=6;
        case 1:
            robot_arm_queue_add(ROBOT_ARM_GET_STORAGE,index++);
            robot_arm_queue_add(ROBOT_PAW_GRIP,index++);
            robot_arm_queue_add(ROBOT_ARM_UP,index++);
            robot_arm_queue_add(ROBOT_ARM_EXCHANGE,index++);
            robot_arm_queue_add(ROBOT_PAW_RELEASE,index++);
            robot_arm_queue_add(ROBOT_ARM_UP,index);
            robot_arm_queue.index+=6;
            break;
        default:
            break;
    }
       reset_storage_count();
}


int get_storage_count() {
    return storage_count;
}


void reset_storage_count() {
    storage_count=0;
}


