/*
 * UART.c
 */

#include "UART.h"


// flag to raise when receive callback called indicate finished
static uint8_t device4_rx_cplt_flag = CALLBACK_FLAG_RESET;

// flag to raise when receive callback called indicate device1 receive finished
static uint8_t device6_rx_cplt_flag = CALLBACK_FLAG_RESET;

//  Rx Transfer completed callback
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == UART_4)
	{
		device4_rx_cplt_flag = CALLBACK_FLAG_SET;
	}
	else if(huart == UART_6)
	{
		device6_rx_cplt_flag = CALLBACK_FLAG_SET;
	}
}


uint8_t CHECK_UART_PROTOCOL(uint8_t data_length, char *data, uint8_t iteration_len)
{

	// buffer for uart device 4 for receiving data
	uint8_t buffer_U4[MAX_DATA_SIZE] = {INIT_VAR};
	// buffer for uart device 6 for receiving data
	uint8_t buffer_U6[MAX_DATA_SIZE] = {INIT_VAR};

	HAL_StatusTypeDef status = HAL_ERROR;

	while(iteration_len)
	{

		// DEVICE 6 -> DEVICE 4
		status = HAL_UART_Receive_DMA(UART_4, buffer_U4, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status  = HAL_UART_Transmit_DMA(UART_6,(uint8_t*)data, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}
		// end commands DEVICE 6 -> DEVICE 4

		// check callback complete flag
		if(wait_till_flag_set_or_timeout(NOT_ADC,UART_4->hdmarx, &device4_rx_cplt_flag, UART_TIMEOUT, UART_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}


		// DEVICE 4 -> DEVICE 6
		status = HAL_UART_Receive_DMA(UART_6, buffer_U6, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status  = HAL_UART_Transmit_DMA(UART_4, (uint8_t*)data, data_length);
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		if(wait_till_flag_set_or_timeout(NOT_ADC,UART_6->hdmarx, &device6_rx_cplt_flag, UART_TIMEOUT, UART_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}


		/* compare the data results at the end of communication with data given by the functions parameters */
		if(strcmp((char*)buffer_U4, (char*)data)!= STRCMP_EQUALS)
		{
			return TEST_FAILED;
		}

		--iteration_len;
	}

	// test passed successfuly
	return TEST_SUCCEED;
}


