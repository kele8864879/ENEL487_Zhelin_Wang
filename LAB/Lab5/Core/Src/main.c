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
#include "stdbool.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* Definitions for blink */
osThreadId_t blinkHandle;
const osThreadAttr_t blink_attributes = {
  .name = "blink",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for rx_cli */
osThreadId_t rx_cliHandle;
const osThreadAttr_t rx_cli_attributes = {
  .name = "rx_cli",
  .priority = (osPriority_t) osPriorityBelowNormal7,
  .stack_size = 128 * 4
};
/* Definitions for status_cli */
osThreadId_t status_cliHandle;
const osThreadAttr_t status_cli_attributes = {
  .name = "status_cli",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 128 * 4
};
/* USER CODE BEGIN PV */
int8_t i=0;flag=0;
uint8_t *p;
uint16_t period = 100;clirxchar=0;
uint8_t cliBufferTX[200];
uint8_t cliBufferRX[20];
bool Newperiod = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

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

  strcpy((char*)cliBufferTX, "\x1b[2J");                                         /*clear the screen*/
  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);
  strcpy((char*)cliBufferTX, "\x1b[0;0H");                                      /*position the cursor*/
  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);
  HAL_UART_Transmit(&huart3, "period:  00100", 14,1000);


  strcpy((char*)cliBufferTX, "\x1b[10;r");                                       /*scroll window*/
  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

  strcpy((char*)cliBufferTX, "\x1b[10;0H");                                      /*position the cursor*/
  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

   strcpy((char*)cliBufferTX, "Testing CLI!\r\n");
   HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

   //HAL_Delay(2000);


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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of blink */
  blinkHandle = osThreadNew(StartDefaultTask, NULL, &blink_attributes);

  /* creation of rx_cli */
  rx_cliHandle = osThreadNew(StartTask02, NULL, &rx_cli_attributes);

  /* creation of status_cli */
  status_cliHandle = osThreadNew(StartTask03, NULL, &status_cli_attributes);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  huart3.Init.BaudRate = 9600;
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
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the blink thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	if(uwTick%period==0)
	HAL_GPIO_TogglePin(GPIOA,LD2_Pin);
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the rx_cli thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
	  if((HAL_UART_Receive(&huart3,cliBufferRX, 1,300) == HAL_OK))
	  {
		  cliBufferTX[i] = cliBufferRX[0];
		  if( cliBufferTX[i]=='\r')
		  {
			cliBufferTX[i]='\0';
			cliBufferRX[0]='\r';
			cliBufferRX[1]='\n';
			HAL_UART_Transmit(&huart3,cliBufferRX,2,1000);
			if(strcmp(cliBufferTX,"period ")==0)
			  {
				period = clirxchar;
                Newperiod = true;
			  }


			 else
			  { strcpy(( char*)cliBufferTX, "error\r\n");
				HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);
			  }
			i=0;
			flag=0;
			clirxchar=0;

		  }

		else if( cliBufferTX[i]=='\177')
			{
			  p=&cliBufferTX[i];
			  HAL_UART_Transmit(&huart3,p,1,1000);
			  i--;
			  if(i<0) i=0;
			}

		else if( cliBufferTX[i]==' ')
		    {
			   flag = 1;
			   p=&cliBufferTX[i];
			   HAL_UART_Transmit(&huart3,p,1,1000);
			   i++;
		    }

		     else
			{
		    	 if(flag==0)
		    	  {
			        p=&cliBufferTX[i];
			        HAL_UART_Transmit(&huart3,p,1,1000);
			        i++;
		    	  }
		    	 else
		    	  {  if(cliBufferRX[0]>=0x30 && cliBufferRX[0]<=0x39)
		    	      {
		    		    cliBufferRX[0] = cliBufferRX[0] - 0x30;
		    		    clirxchar = clirxchar *10 + cliBufferRX[0];
		    		    p=&cliBufferTX[i];
		    		   	HAL_UART_Transmit(&huart3,p,1,1000);
		    		   	//i++;
		    	      }
		    	  }
			}
	}

    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the status_cli thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */

	uint8_t j;
  for(;;)
  {
	if(Newperiod==true)
	{
	  strcpy((char*)cliBufferRX, "\x1b[s");                                            /*save cursor*/
	  HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
	  strcpy((char*)cliBufferRX, "\x1b[0;0H");
	  HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
      strcpy((char*)cliBufferRX, "period:  ");
      HAL_UART_Transmit(&huart3,cliBufferRX, strlen((char*)cliBufferRX),1000);

      uint16_t temp = period;
      for( j=0;j<5;j++)
       {  cliBufferRX[4-j]=(temp%10)^0x30;
          temp=temp/10;
       }

      cliBufferRX[5]='\0';
      HAL_UART_Transmit(&huart3,cliBufferRX, strlen((char*)cliBufferRX),1000);

      strcpy((char*)cliBufferRX, "\x1b[u");                                            /*恢复光标*/
	  HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
	  Newperiod = false;
	}

    osDelay(1);
  }
  /* USER CODE END StartTask03 */
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

