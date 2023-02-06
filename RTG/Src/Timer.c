/*
 * Timer.c
*/

#include"Timer.h"

uint32_t Sec_Count = INIT_ZERO;
uint32_t Start_Time = INIT_ZERO;
uint32_t End_Time = INIT_ZERO;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == TIM_7)
	{
		Sec_Count++;
    }
}


uint8_t CheckTIMER(uint8_t usr_iter)
{

	Start_Time = INIT_ZERO;
	End_Time = INIT_ZERO;


	//We go into loop for iter of usr
	while(usr_iter)
	{

		//Get the time of sys
		Start_Time = HAL_GetTick();;

		if( HAL_TIM_Base_Start_IT(TIM_7) != HAL_OK)
		{
			return TEST_FAILED;
		}

		//Start a while loop count to minute
		while(Sec_Count != MINUTE){}

		//Stop clk stop Timer
		HAL_TIM_Base_Stop_IT(TIM_7);

		//Give the end of time
		End_Time = HAL_GetTick();

		if( (End_Time - Start_Time)/THOSD > MAX_VAL ||  (End_Time - Start_Time)/THOSD < MIN_VAL )
			{
				return TEST_FAILED;
			}


		--usr_iter;
	}

	return TEST_SUCCEED;
}
