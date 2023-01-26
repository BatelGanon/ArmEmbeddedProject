/*
 * SPI.c
 */

#include "SPI.h"


// callback flag when receive is done
static	uint8_t  spi_master_cplt_callback_flag = CALLBACK_FLAG_RESET;

// callback flag when receive is done
static	uint8_t  spi_slave_cplt_callback_flag = CALLBACK_FLAG_RESET;

//  Tx and Rx Transfer completed callback
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi == SPI_1)
	{
		spi_master_cplt_callback_flag = CALLBACK_FLAG_SET;
	}
	else if(hspi == SPI_5)
	{
		spi_slave_cplt_callback_flag = CALLBACK_FLAG_SET;
	}
}


/* the SPI under unit testing function which perform the actual tests according to number of
   iterations, each iteration checks if the sent data value equal to the master buffer
   after sending back to the master */

uint8_t CheckSPI(uint8_t data_length, uint8_t *data, uint8_t iteration_len)
{

	// holding the data received back in master at the end of each iteration
	uint8_t buffer_SPI1[MAX_DATA_SIZE] = {INIT_VAR};
	// holding the data received and sent back by the slave in each iteration
	uint8_t buffer_SPI5[MAX_DATA_SIZE] = {INIT_VAR};

	HAL_StatusTypeDef status = HAL_ERROR;

	while (iteration_len)
	{

		// MASTER -> SLAVE
		status = HAL_SPI_TransmitReceive_DMA(SPI_5, buffer_SPI5, buffer_SPI5, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_1, data, buffer_SPI1, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		// check callback complete flag
		if(wait_till_flag_set_or_timeout(NOT_ADC, SPI_5->hdmarx, &spi_slave_cplt_callback_flag, SPI_TIMEOUT, SPI_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		// SLAVE -> MASTER
		status = HAL_SPI_TransmitReceive_DMA(SPI_5,buffer_SPI5, buffer_SPI5, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_SPI_TransmitReceive_DMA(SPI_1, buffer_SPI1, buffer_SPI1, data_length);
		if (status != HAL_OK)
		{
			return FALSE;
		}

		// check callback complete flag
		if(wait_till_flag_set_or_timeout(NOT_ADC,SPI_1->hdmarx, &spi_master_cplt_callback_flag, SPI_TIMEOUT, SPI_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		// end of iteration test if sent data is not equal to buffer at the end the peripheral not working correctly, test failed
		if(strcmp((char*)SPI_1, (char*)data)!=STRCMP_EQUALS)
		{
			return TEST_FAILED;
		}

		--iteration_len;

	}

	/* if all the tests iterations passed (bit_pattern equals master_buffer in every iteration) than the peripheral is working correctly,
	   test passed */

	return TEST_SUCCEED;
}

