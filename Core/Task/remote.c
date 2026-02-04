//
// Created by llzz53 on 2026/1/10.
//

#include <main.h>
#include <usart.h>
#include "cmsis_os2.h"


#include "chassis.h"
#include "remote.h"
#include "vision.h"
#include "arm_and_gimbal.h"


#include "../APP/bluetooth.h"


static cmd_type remote_cmd_type;

void RTOS_Task_Remote(void *argument)
{
    bluetooth_init();
    remote_cmd_type=NO_CMD;
    for(;;)
    {
        distribute_cmd();
        osDelay(10);
    }


}

void distribute_cmd() {
    if(get_cmd_head()==COMMAND_HEAD&&get_cmd_size()==COMMAND_SIZE){
        switch (get_cmd_type()) {
            case CHASSIS_CMD:
                remote_cmd_type=CHASSIS_CMD;
                chassis_set_cmd(get_cmd());
                break;
            case VISION_CMD:
                remote_cmd_type=VISION_CMD;
                vision_task_on();
                break;
            case GIMBAL_CMD:
                remote_cmd_type=GIMBAL_CMD;
                break;
            case ARM_CMD:
                remote_cmd_type=ARM_CMD;
                break;
            default:
                break;
        }
    }
}

cmd_type remote_get_cmd();
