/*
 * I2C.c
 */

#include "I2C.h"

// I2C_1 -> MASTER
// I2C_2  -> SLAVE

// i2c master callback flag indicate receive completed
static uint8_t i2c_master_rcv_callback_flag = CALLBACK_FLAG_RESET;

// i2c slave callback flag indicate receive completed
static uint8_t i2c_slave_rcv_callback_flag = CALLBACK_FLAG_RESET;

// Master Rx Transfer completed callback
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == I2C_1)
	{
		i2c_master_rcv_callback_flag = CALLBACK_FLAG_SET ;
	}
}

// Slave Rx Transfer completed callback
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == I2C_2)
	{
		i2c_slave_rcv_callback_flag = CALLBACK_FLAG_SET ;
	}
}


/*the I2C under unit test, tests if bit pattern equals to the same data received after
  completing a communication cycle (data sent as follows: Master -> Slave -> Master)*/
uint8_t CheckI2C(uint8_t data_length, uint8_t *data, uint8_t iteration_len)
{

	// buffer for master device for receiving data
	uint8_t buffer_I2C1[MAX_DATA_SIZE] = {INIT_VAR};

	// buffer for slave device for receiving data
	uint8_t buffer_I2C2[MAX_DATA_SIZE] = {INIT_VAR};

	// check status of receive transmit, error detection
	HAL_StatusTypeDef status = HAL_ERROR;

	while (iteration_len){

		// Master -> Slave
		status = HAL_I2C_Slave_Receive_DMA(I2C_2, buffer_I2C2, data_length);

		if (status != HAL_OK)
		{
			return TEST_FAILED;
		}

		//Master transmit the data we got in the function to slave by DMA
		status = HAL_I2C_Master_Transmit_DMA(I2C_1, hi2c1.Init.OwnAddress1, data, data_length);
		if (status != HAL_OK)
		{
			return TEST_FAILED;
		}

		// check callback complete flag
		if(wait_till_flag_set_or_timeout(NOT_ADC,I2C_1->hdmarx,&i2c_slave_rcv_callback_flag, I2C_TIMEOUT, I2C_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
	    }
		// end commands Master -> Slave

		// Slave -> Master
		status = HAL_I2C_Master_Receive_DMA(I2C_1, hi2c2.Init.OwnAddress2, buffer_I2C1, data_length);
		if (status != HAL_OK)
		{
			return TEST_FAILED;
		}

		status = HAL_I2C_Slave_Transmit_DMA(I2C_2, buffer_I2C2, data_length);
		if (status != HAL_OK)
		{
			return FALSE;
		}

		// check callback complete flag
		if(wait_till_flag_set_or_timeout(NOT_ADC,I2C_2->hdmarx,&i2c_master_rcv_callback_flag, I2C_TIMEOUT, I2C_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}

		// compare the data results at the end of communication with data given by the functions parameters
		if(strcmp((char*)buffer_I2C1, (char*)data)!=STRCMP_EQUALS)
		{
			/* test did not pass, test failed */
			return TEST_FAILED;
		}
		--iteration_len;
	}

	// test passed successfuly
	return TEST_SUCCEED;
}


