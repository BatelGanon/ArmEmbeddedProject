/*
 * ADC.h
 *
 * ADC1 : PA0
 *
 */

#include "main.h"
#include <stdbool.h>

extern ADC_HandleTypeDef hadc1;
#ifndef INC_ADC_H_
#define INC_ADC_H_
#define ADC_1 (&hadc1)
//#define MAX_VOLT 5000
//#define MIN_VOLT 3000
#define ADC_EXPECTED_VALUE 4096
#define ADC_DEVIATION 80
#define ADC_FLAG_SET 1
#define ADC_HANDLE_ADDR (&hadc1)
#define ADC_TO_TEST ADC1
#define ADC_NUM_OF_SAMPLES 1
#define ADC_DMA_TIME 0
#define ADC_TIMEOUT 50

/**@brief holding the actual value got by the ADC. */
extern uint32_t adc_value;

/**@brief the flag of the adc when interrupt ISR called */
extern uint8_t adc_callback_flag;

/**@brief the handle of the ADC peripheral */
extern ADC_HandleTypeDef hadc1;

// function convert volt from analog to digital
// we get an voltage from GPIO pin and check if it in the exepted range
//uint8_t CHECK_ADC_PROTOCOL();
uint8_t CheckADC(uint8_t iterations_len);
#endif /* INC_ADC_H_ */
