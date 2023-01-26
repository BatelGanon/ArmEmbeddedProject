
/*
 * RTG.h
 *
 *  Created on: Oct 2, 2022
 *      Author: RTG
 *
 */

///////////////////////////////////////////////// this is the new RTG.H:///////////////////////////
#ifndef INC_RTG_H_
#define INC_RTG_H_
#include "main.h"
#include "lwip.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UART.h"
#include "I2C.h"
#include "SPI.h"
#include "Timer.h"
#include "ADC.h"
#include <string.h>
#include <stdbool.h>

extern UART_HandleTypeDef huart3;
#define UART_DEBUG &huart3

#define SERVER_PORT 7

extern struct netif gnetif;	//Generic data structure used for all lwIP network interfaces.

#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13
#define TRUE 1


void rtg_main();

#endif /* INC_RTG_H_ */


