/*
 * ADC.c
 *
 */
#include "ADC.h"
#include <stdbool.h>

/* the adc under unit tests function, the function checks if the adc value got is the expected value.
   the expected value is according to which the ADC peripheral connected to */
uint8_t CheckADC(uint8_t iterations_len)
{
	// start the dma functionality
	HAL_ADC_Start_DMA(ADC_HANDLE_ADDR, &adc_value, (uint32_t)ADC_NUM_OF_SAMPLES);

	/* the status to check the functions in the iterations */
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations_len)
	{

		// start ADC convertion
		status = HAL_ADC_Start(ADC_HANDLE_ADDR);

		// check if start correctly
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		// check callback complete flag
		if(wait_till_flag_set_or_timeout(IS_ADC,ADC_HANDLE_ADDR->DMA_Handle, &adc_callback_flag, ADC_TIMEOUT, ADC_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}
		else
		{
			// check if ADC expected value is between the deviation allowed ADC_VAL +/- DEVIATION if it is continue to next iteration
			if(! (ADC_EXPECTED_VALUE - ADC_DEVIATION <= adc_value && adc_value <= ADC_EXPECTED_VALUE + ADC_DEVIATION ))
			{
				// reset the callback flag
				adc_callback_flag = CALLBACK_FLAG_RESET;
				return TEST_FAILED;
			}
			// reset the callback flag
			adc_callback_flag = CALLBACK_FLAG_RESET;

		}

		--iterations_len;
	}

	// if all iterations passed return TEST passed successfully
	return TEST_SUCCEED;
}
