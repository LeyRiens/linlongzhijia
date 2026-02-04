//
// Created by llzz53 on 2026/1/14.
//

#include "servo_arm.h"

#include "cmsis_os2.h"
#include "tim.h"


const uint8_t up_2_storage[SERVO_COUNT][TRAJ_SIZE];
const uint8_t up_2_exchange[SERVO_COUNT][TRAJ_SIZE];
const uint8_t up_2_low[SERVO_COUNT][TRAJ_SIZE];
const uint8_t up_2_vision[SERVO_COUNT][TRAJ_SIZE];
const uint8_t up_2_get_storage[SERVO_COUNT][TRAJ_SIZE];


const uint8_t (*traj_table[6])[SERVO_COUNT][TRAJ_SIZE]=
    {NULL,&up_2_low,&up_2_storage,&up_2_get_storage,&up_2_exchange,&up_2_vision};


servo_action arm_servos_state={
        .current_position=UP,
        .traj=NULL,
        .state=ARM_READY,
};


void servo_arm_init() {
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 9);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 9);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 9);
}

void servo_set_traj(arm_position arm_destination) {
    if (arm_destination==arm_servos_state.current_position){
        return;
    }
    if(arm_servos_state.current_position==UP) {
        arm_servos_state.traj=traj_table[arm_destination];
        arm_servos_state.direction=ARM_DIRECTION_POSITIVE;
        arm_servos_state.index=0;
    }else {
        arm_servos_state.traj=traj_table[arm_servos_state.current_position];
        arm_servos_state.direction=ARM_DIRECTION_NEGATIVE;
        arm_servos_state.index=TRAJ_SIZE-1;
    }
    arm_servos_state.state=ARM_RUNNING;
    arm_servos_state.current_position=arm_destination;
}

void servo_arm_traj_update() {
    if (arm_servos_state.state==ARM_READY || arm_servos_state.traj==NULL) {
        return;
    }
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (*arm_servos_state.traj)[0][arm_servos_state.index]);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (*arm_servos_state.traj)[1][arm_servos_state.index]);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (*arm_servos_state.traj)[2][arm_servos_state.index]);
    arm_servos_state.index+=arm_servos_state.direction;
    if (arm_servos_state.index<0 || arm_servos_state.index>=TRAJ_SIZE) {
        arm_servos_state.state=ARM_READY;
    }
}

void servo_arm_set_state(arm_state state) {
    arm_servos_state.state=state;
}

arm_state servo_arm_get_state() {
    return arm_servos_state.state;
}
