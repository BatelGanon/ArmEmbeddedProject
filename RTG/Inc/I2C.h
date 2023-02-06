/*
 * I2C.h
 *
 *Master: I2C1
 *SCL PB6
 *SDA PB9
 *Slave: I2C2
 *SCL PB10
 *SDA PB11
 */

#include "main.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#ifndef INC_I2C_H_

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

#define INC_I2C_H_
#define I2C_1 (&hi2c1)
#define I2C_2 (&hi2c2)
#define MAX_DATA_SIZE 256
#define INIT_VAR 0
#define TRUE 1
#define FALSE 0
#define EQUAL_ZERO 0

#define I2C_DMA_TIME 20
#define I2C_TIMEOUT 50




// Function get data, length and iteration number
// transmit the data from master to slave buffer by DMA
//then transmit from slave buffer to master buffer and compare the data with the master buffer
uint8_t CheckI2C(uint8_t data_length, char *data, uint8_t iteration_len);




#endif /* INC_I2C_H_ */
