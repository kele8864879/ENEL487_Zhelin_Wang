/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../Mycode/CLI/CLI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 128 * 4
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .priority = (osPriority_t) osPriorityBelowNormal5,
  .stack_size = 128 * 4
};
/* Definitions for CLI_Queue */
osMessageQueueId_t CLI_QueueHandle;
const osMessageQueueAttr_t CLI_Queue_attributes = {
  .name = "CLI_Queue"
};
/* Definitions for Status_Queue */
osMessageQueueId_t Status_QueueHandle;
const osMessageQueueAttr_t Status_Queue_attributes = {
  .name = "Status_Queue"
};
/* USER CODE BEGIN PV */
int x = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
void Status_CLI_Task(void *argument);
void RX_CLI_Task(void *argument);
void stateControllerTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  clean_screen;
  transmit;
  cursor0_0
  transmit;
  scroll_window
  transmit;
  cursor10_0
  transmit;
  strcpy((char*)cliBufferTX, "Welcome!\r\n");
  transmit;
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of CLI_Queue */
  CLI_QueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &CLI_Queue_attributes);

  /* creation of Status_Queue */
  Status_QueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &Status_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(Status_CLI_Task, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(RX_CLI_Task, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(stateControllerTask, NULL, &myTask03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA6 PA7 PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC5 PC6 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void printStringBlocking(const char* message)
{
    int i = 0;
    HAL_StatusTypeDef	st;

    //Have to wait for the last transmission to go.
    while (huart2.gState == HAL_UART_STATE_BUSY_TX) {}

    for (const char* p = message; *p; ++p) {
        cliBufferTX[i] = *p;
        i++;
    }
    st = HAL_UART_Transmit(&huart2, cliBufferTX, i, 1000);
    if (st != HAL_OK)
    {
        Error_Handler();
    }

}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_Status_CLI_Task */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Status_CLI_Task */
void Status_CLI_Task(void *argument)
{
  /* USER CODE BEGIN 5 */
	 uint16_t statusMessage;
	 uint16_t message;
	 osStatus_t status;
	 uint8_t period[3];

  /* Infinite loop */
  for(;;)
  {
	  {
		  status = osMessageQueueGet(Status_QueueHandle, &statusMessage, NULL, 0U);
		        if (status == osOK)
		        {
		        	message = statusMessage;
		        	 if (message == 1)
		        			        {
		        		 	 	 	 itoa(x,period,10);
		        		 	 	 	save_cursor;
		        		 	 	 	transmit;
		        			  		  cursor0_0;
		        			  		  transmit;
		        			  		clean_line;
		        			  		  transmit;
		        			  		  strcpy(( char*)cliBufferTX, "scm mode. ");
		        			    	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
		        			    	  HAL_UART_Transmit(&huart2, period, strlen((char*)period),1000);
		        			  		  strcpy(( char*)cliBufferTX, " is the atm value");
		        			    	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
		        			    	  go_to_saved_cursor_point;
		        			    	  transmit;

		        			        }
		        	 else if (message == 2)
		        			       		  {
		        		 	 	 	 	 itoa(x,period,10);
		        		 	 	 	 	save_cursor;
		        		 	 	 	 	transmit;
		        				  		  cursor0_0;
		        				  		  transmit;
		        				  		clean_line;
		        				  		  transmit;
		        				  		  strcpy(( char*)cliBufferTX, "fsm mode. ");
		        				    	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
			        			    	  HAL_UART_Transmit(&huart2, period, strlen((char*)period),1000);
			        			  		  strcpy(( char*)cliBufferTX, " is the atm value");
			        			    	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
			        			    	  go_to_saved_cursor_point;
		        				    	  transmit;
		        			       		  }
		        }


	  }
    osDelay(100);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_RX_CLI_Task */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RX_CLI_Task */
void RX_CLI_Task(void *argument)
{
  /* USER CODE BEGIN RX_CLI_Task */
	uint16_t cliMessage;
	int8_t i=0;
	uint8_t *p;
	uint8_t cliBufferTX[200];
  /* Infinite loop */
  for(;;)
  {
	  if((HAL_UART_Receive(&huart2,cliBufferRX, 1,300) == HAL_OK))
	  {
		  cliBufferTX[i] = cliBufferRX[0];
		  if( cliBufferTX[i]=='\r')
		 		  {
		 			cliBufferTX[i]='\0';
		 			cliBufferRX[0]='\r';
		 			cliBufferRX[1]='\n';
		 			HAL_UART_Transmit(&huart2,cliBufferRX,2,1000);
					if(strcmp(cliBufferTX,"help")==0)
					  {
						  cursor0_0;
						  transmit;
						  clean_screen;
						  transmit;
				  	  	  strcpy(( char*)cliBufferTX, "enter scm,fsm,or atm x");
				  	  	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
				  	  	  cursor10_0;
				  	  	  transmit;
					  }
					else if(strcmp(cliBufferTX,"scm")==0)
					  {
						cliMessage = 1;
						 if (osMessageQueuePut(CLI_QueueHandle, &cliMessage, 1U, 0U) != osOK)
								 		                {
								 		                    Error_Handler();
								 		                }
					  }
					else if(strcmp(cliBufferTX,"fsm")==0)
					  {
						cliMessage = 2;
						 if (osMessageQueuePut(CLI_QueueHandle, &cliMessage, 1U, 0U) != osOK)
								 		                {
								 		                    Error_Handler();
								 		                }
					  }
					else if(cliBufferTX[0]=='a' && cliBufferTX[1] == 't' && cliBufferTX[2] == 'm' && cliBufferTX[3] == ' ')
					  {
						cliMessage = 3;
						uint8_t num[3];
						num[0] = cliBufferTX[4];
						num[1] = cliBufferTX[5];
						num[2] = cliBufferTX[6];

						x = atoi(num);
						if ((x >= 1) && (x <= 100))
						{
				 			if (osMessageQueuePut(CLI_QueueHandle, &cliMessage, 1U, 0U) != osOK)
				 											 		                {
				 											 		                    Error_Handler();
				 											 		                }
						}
						else {
							invalid_command;
							HAL_UART_Transmit(&huart2, cliBufferRX, strlen((char*)cliBufferRX),1000);
							transmit;
				 			cliBufferTX[i]='\0';
				 			cliBufferRX[0]='\r';
				 			cliBufferRX[1]='\n';
				 			HAL_UART_Transmit(&huart2,cliBufferRX,2,1000);
							}
					  }

					else
											{
											invalid_command;
											HAL_UART_Transmit(&huart2, cliBufferRX, strlen((char*)cliBufferRX),1000);
											transmit;
								 			cliBufferTX[i]='\0';
								 			cliBufferRX[0]='\r';
								 			cliBufferRX[1]='\n';
								 			HAL_UART_Transmit(&huart2,cliBufferRX,2,1000);
											}
		 		    i=0;
		 		  }
		  else if( cliBufferTX[i]=='\177')
		  			{
		  			  p=&cliBufferTX[i];
		  			  HAL_UART_Transmit(&huart2,p,1,1000);
		  			  i--;
		  			  if(i<0) i=0;
		  			}
		  else if( cliBufferTX[i]==' ')
		  		    {
		  			   p=&cliBufferTX[i];
		  			   HAL_UART_Transmit(&huart2,p,1,1000);
		  			   i++;
		  		    }
		  else
		 			{
			  	  	   p=&cliBufferTX[i];
		 			   HAL_UART_Transmit(&huart2,p,1,1000);
		 			   i++;
		 			}
	  }
    osDelay(1);
  }
  /* USER CODE END RX_CLI_Task */
}

/* USER CODE BEGIN Header_stateControllerTask */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_stateControllerTask */
void stateControllerTask(void *argument)
{
	  uint16_t cliMessage;
		  uint16_t statusMessage = 2;
		  osStatus_t status;
		  int sequence_fsm = 0;
		  int sequence_scm = 0;


		    //Send a status message straight away




		  /* Infinite loop */
	  for(;;)
	  {
		  status = osMessageQueueGet(CLI_QueueHandle, &cliMessage, 1U, 0U);
		  if (status == osOK)
		  {
			  statusMessage = cliMessage;
			  if (osMessageQueuePut(Status_QueueHandle, &statusMessage, 1U, 0U) != osOK)
			  		    {
			  		        Error_Handler();
			  		    }
		  }

		  	  if (statusMessage == 1)	// 0S - 70.5S
		  	  {
		  		  if (sequence_scm == 0)
		  		  {
		  			P_RED_CLOSE;
		  			P_YELLOW_CLOSE;
		  			P_GREEN_OPEN;
		  			P_BLUE_OPEN;
		  			S_RED_OPEN;
		  			S_YELLOW_CLOSE;
		  			S_GREEN_CLOSE;
		  			S_BLUE_CLOSE;
		  			osDelay(70500/x);
		  			sequence_scm++;

		  		  }
		  		  else if (sequence_scm == 1) // 70.5S - 83.5S
		  		{
		  			for(int Primary_WW = 0; Primary_WW<13; Primary_WW++)
		  			{
		  				P_BLUE_TOG;
						osDelay(1000/x);
		  			}
		  			sequence_scm++;
		  		}
		  		  else if (sequence_scm == 2) //83.5s - 87s
		  		{
		  			P_BLUE_CLOSE;
		  			P_YELLOW_OPEN;
		  			P_GREEN_CLOSE
		  			osDelay(3500/x);
		  			sequence_scm++;
		  		}
		  		  else if (sequence_scm == 3) //87s - 93s
		  		{
		  			P_RED_OPEN;
		  			P_YELLOW_CLOSE;
		  			osDelay(6000/x);
		  			sequence_scm++;
		  		}
		  		  else if (sequence_scm == 4)//93s - 113s
		  		{
		  			S_RED_CLOSE;
		  			S_GREEN_OPEN;
		  			S_BLUE_OPEN;
		  			osDelay(20000/x);
		  			sequence_scm++;
		  		}
		  		  else if (sequence_scm == 5)//113s - 121s
		  		{
		  			for(int Secondary_WW = 0; Secondary_WW<8; Secondary_WW++)
		  			{
		  			S_BLUE_TOG;
		  			osDelay(1000/x);
		  			}
		  			sequence_scm++;
		  		}
		  		  else if (sequence_scm == 6)//121s-124.5s
		  		{
		  			sequence_scm=0;
		  			S_GREEN_CLOSE;
		  			S_YELLOW_OPEN;
		  			for(int Secondary_WW = 0; Secondary_WW<3; Secondary_WW++)
		  			{
		  			S_BLUE_TOG;
		  			osDelay(1000/x);
		  			}

		  		}
		  	  }
		  	  else  if (statusMessage == 2)	//fsm mode
			  {
				  if (sequence_fsm == 0)
				  {
					  P_YELLOW_CLOSE;
					  P_GREEN_CLOSE;
					  P_BLUE_CLOSE;
					  S_YELLOW_CLOSE;
					  S_GREEN_CLOSE;
					  S_BLUE_CLOSE;
					  P_RED_OPEN;
					  S_RED_OPEN;
					  osDelay(1500/x);
					  sequence_fsm++;
				  }
				  if(sequence_fsm == 1)
				  {
					  P_RED_TOG;
					  S_RED_TOG;
					  osDelay(500/x);
					  sequence_fsm = 0;
				  }

			  }

	  }
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

