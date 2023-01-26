/*
 * Timer.h
 *
 * TIM7
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#include <stdbool.h>

extern TIM_HandleTypeDef htim7;

#define MINUTE 60
#define THOSD 1000
#define TIM7 &htim7
#define TRUE 1
#define FALSE 0
#define INIT_ZERO 0
#define MAX_VAL 65
#define MIN_VAL 55


// Function get iteration number,
// will initalize the vars for holding time
// then counter tick's for a minute and check if then  checks timer validation
uint8_t CheckTIMER(uint8_t usr_iter);



#endif /* INC_TIMER_H_ */
