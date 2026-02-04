//
// Created by llzz53 on 2026/1/10.
//

#include "bluetooth.h"
#include <usart.h>
#include <main.h>

extern DMA_HandleTypeDef hdma_usart1_rx;
uint8_t buffer_a[BUFFER_SIZE];
uint8_t buffer_b[BUFFER_SIZE];

uint8_t *buffer_read;
uint8_t *buffer_write;




void bluetooth_receive_start() {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, buffer_write, BUFFER_SIZE);
    __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}


void bluetooth_init()
{
    buffer_read=buffer_a;
    buffer_write=buffer_b;
    bluetooth_receive_start();
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart == &huart1)
    {

        buffer_write=buffer_read;

        buffer_read==buffer_a?buffer_read=buffer_b:buffer_a;

    }
    bluetooth_receive_start();
}


uint8_t get_cmd_head() {
    return buffer_read[0];
}

uint8_t get_cmd_size() {
    return buffer_read[1];
}

uint8_t get_cmd_type() {
    return buffer_read[2];
}

uint8_t get_cmd() {
    return buffer_read[3];
}