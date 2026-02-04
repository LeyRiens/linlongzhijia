//
// Created by llzz53 on 2026/1/27.
//
#include "main.h"
#include "tim.h"
#include "servo_paw.h"

#define COMPARE_PAW_GRIP 0
#define COMPARE_PAW_RELEASE 99
paw_state current_paw_state;
void servo_paw_update() {


}



void servo_paw_grip();
void servo_paw_release();

void servo_paw_init() {
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, COMPARE_PAW_RELEASE);
    current_paw_state=PAW_READY;
}

void servo_paw_set_state(paw_state state) {
    current_paw_state = state;
}
paw_state servo_paw_get_state() {
    return current_paw_state;
}
