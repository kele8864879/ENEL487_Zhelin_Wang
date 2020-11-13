/*
 * timer.c
 *
 *  Created on: Nov 1, 2020
 *      Author: Zhelin Wang
 */
#include "timer.h"


int16_t timer_start(void)
{
	int16_t current = __HAL_TIM_GET_COUNTER(&htim4);
	return current;
}



uint16_t timer_stop(int16_t previous)
{
	int16_t temp = __HAL_TIM_GET_COUNTER(&htim4);
	uint16_t ticks = previous - temp;

	return ticks;
}


void tickasc(uint32_t Hex)
{
	uint8_t j;
    char result[20];
    strcpy((char*)result, "       ticks\r\n");

	for( j = 0;j < 6; j++)
     {  result[5-j] = (Hex%10)^0x30;
      Hex = Hex / 10;
     }

    HAL_UART_Transmit(&huart2, result, strlen((char*)result),1000);

}


