//
// Created by llzz53 on 2026/1/14.
//

#include "raser.h"
#include <usart.h>

void raser_on() {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
}

void raser_off() {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
}
