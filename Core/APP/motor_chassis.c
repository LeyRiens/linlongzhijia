//
// Created by llzz53 on 2026/1/19.
//

#include "motor_chassis.h"
#include "pid.h"
#include <../Inc/tim.h>



const int8_t motor_output_move_table[9][2]=
    {{1,1},{1,0}, {1,-1},
    {0,1},{0,0},{0,-1},
    {-1,1},{-1,0},{-1,-1}};

const int8_t (motor_output_spin_table[3])={1,0,-1};

uint16_t motor_final_output[4] = {0, 0, 0, 0};
float motor_target_output[4] = {0, 0, 0, 0};

void motor_final_output_set(uint16_t final_output,uint8_t id) {
    motor_final_output[id] =final_output ;
}

void motor_target_output_set(float target,uint8_t id) {
    motor_target_output[id] = target;
}



void motor_output_update() {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, motor_final_output[0] );
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, motor_final_output[1] );
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, motor_final_output[2] );
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, motor_final_output[3] );
}

int8_t motor_get_speed_x(uint8_t cmd)
{
    return motor_output_move_table[cmd][0];
}

int8_t motor_get_speed_y(uint8_t cmd) {
    return motor_output_move_table[cmd][1];
}

void motor_set_direction() {
    if (motor_target_output[0]>=0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    }else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    }
    if (motor_target_output[1]>=0) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }
    if (motor_target_output[2]>=0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    }else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    }
    if (motor_target_output[3]>=0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    }else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    }
}



void motor_stop() {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
}


float motor_get_target_speed(uint8_t id) {
    return motor_target_output[id];
}

//////由于c8t6引脚不够，等待更换板子后再补充完成//////
float motor_get_current_speed(uint8_t id) {
    return 0.0f;
}


/////////普通轮电机控制函数（未使用PID)///////
// void motor_Speed_Left() {
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 19);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 19);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 59);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 59);
// }
//
// void motor_Speed_Right() {
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 59);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 59);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 19);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 19);
// }
//
// void motor_Speed_Forward() {
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 59);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 59);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 59);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 59);
// }
//
// void motor_Speed_Stop() {
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
//     __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
// }
//
// void motor_Direction_Forward() {
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
// }
//
// void motor_Direction_Backward() {
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
// }
//
// void motor_Direction_Spinleft() {
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
//     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
// }
//
// void motor_Direction_Spinright() {
//         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
//         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
// }
//