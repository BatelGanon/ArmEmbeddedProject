/*
 * UART.h
 *
 *UART4 :
 *RX PC11
 *TX PC10
 *
 *UART6:
 *RX PC7
 *TX PC6
 */
#pragma once

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern UART_HandleTypeDef huart3;	//Change to match your UART number
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;


#define UART_1            &huart3				//Change to match your UART number
#define UART_4            (&huart4)
#define UART_6            (&huart6)
#define MAX_DATA_SIZE     256
#define INIT_VAR          0
#define EQUAl_ZERO        0
#define TRUE              1
#define FALSE             0

#define UART_TIMEOUT      50
#define UART_DMA_TIME     10

// Function get data, size and interation number and transmit the data with uart4 to uart6 buffer,
// then transmit the data from uart6 buffer to uart4 buffer and then compare with the data
uint8_t CheckUART(uint8_t data_length, uint8_t *data, uint8_t iteration_len);

