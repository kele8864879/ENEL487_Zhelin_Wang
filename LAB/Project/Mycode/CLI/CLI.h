#ifndef __CLI_H__
#define __CLI_H__

#include "main.h"




uint8_t cliBufferTX[200];
uint8_t cliBufferRX[200];
uint8_t cliRXChar;




#define clean_screen strcpy((char*)cliBufferTX, "\x1b[2J");
#define cursor0_0   strcpy((char*)cliBufferTX, "\x1b[0;0H");
#define scroll_window strcpy((char*)cliBufferTX, "\x1b[10;r");
#define cursor10_0 strcpy((char*)cliBufferTX, "\x1b[10;0H");
#define invalid_command strcpy((char*)cliBufferRX, "invalid command: ");
#define clean_line strcpy((char*)cliBufferTX, "\x1b[1J");
#define save_cursor strcpy((char*)cliBufferTX, "\x1b[s");
#define go_to_saved_cursor_point strcpy((char*)cliBufferTX, "\x1b[u");
#define transmit HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);

#define P_RED_TOG HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_6); //PRIMARY Red
#define P_YELLOW_TOG HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_7);	//PRIMARY YELLOW
#define P_GREEN_TOG HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8);	//PRIMARY GREEN
#define P_BLUE_TOG HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_9); //PRIMARY WALK BLUE
#define S_RED_TOG HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9); //SECONDARY RED
#define S_YELLOW_TOG HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_6); //SECONDARY YELLOW
#define S_GREEN_TOG HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8); //SECONDARY GREEN
#define S_BLUE_TOG HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_5); //SECONDARY WALK BLUE

#define P_RED_OPEN HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); // PRIMARY WAKL RED OPEN
#define P_YELLOW_OPEN HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); // PRIMARY WAKL YELLOW OPEN
#define P_GREEN_OPEN HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); // PRIMARY WAKL GREEN OPEN
#define P_BLUE_OPEN HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // PRIMARY WAKL BLUE OPEN
#define S_RED_OPEN HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); // PRIMARY WAKL RED OPEN
#define S_YELLOW_OPEN HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); // PRIMARY WAKL YELLOW OPEN
#define S_GREEN_OPEN HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); // PRIMARY WAKL GREEN OPEN
#define S_BLUE_OPEN HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET); // PRIMARY WAKL BLUE OPEN

#define P_RED_CLOSE HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // PRIMARY WAKL RED CLOSE
#define P_YELLOW_CLOSE HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET); // PRIMARY WAKL YELLOW CLOSE
#define P_GREEN_CLOSE HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // PRIMARY WAKL GREEN CLOSE
#define P_BLUE_CLOSE HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // PRIMARY WAKL BLUE CLOSE
#define S_RED_CLOSE HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // PRIMARY WAKL RED CLOSE
#define S_YELLOW_CLOSE HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // PRIMARY WAKL YELLOW CLOSE
#define S_GREEN_CLOSE HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // PRIMARY WAKL GREEN CLOSE
#define S_BLUE_CLOSE HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET); // PRIMARY WAKL BLUE CLOSE

#endif
