/*
 * SPI.h
 *
 *
 * Master: SPI1
 * MOSI PB5
 * MISO PA6
 * SCK PA5
 *
 * Slave: SPI5
 * MOSI PF9
 * MISO PF8
 * SCK PF7
 *
 *
 */
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi5;

#define SPI_1            (&hspi1)
#define SPI_5            (&hspi5)
#define MAX_DATA_SIZE    256
#define MAX_DATA_SIZE    256
#define INIT_VAR         0
#define FLAG_UP          1

#ifndef INC_SPI_H_
#define INC_SPI_H_
#define TRUE             1
#define FALSE            0
#define EQUAL_ZERO       0

#define SPI_TIMEOUT      50
#define SPI_DMA_TIME     10

//function get data, length, and iteration number,
// and transmit the data from SP1 - the master to SPI5 (the slave) buffer,
// then transmit the data from SPI5 buffer to SPI1 buffer
//and compare the buffer of SPI1 with the data we got in the function and return true is they equal
uint8_t CheckSPI(uint8_t data_length, char *data, uint8_t iteration_len);

#endif /* INC_SPI_H_ */
