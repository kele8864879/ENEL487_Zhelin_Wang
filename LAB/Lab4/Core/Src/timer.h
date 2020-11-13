/*
 * timer.h
 *
 *  Created on: Nov 1, 2020
 *      Author: Zhelin Wang
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <main.h>

UART_HandleTypeDef huart2;
TIM_HandleTypeDef htim4;

int16_t timer_start(void);
uint16_t timer_stop(int16_t previous);

void tickasc(uint32_t Hex);


#endif /* SRC_TIMER_H_ */
