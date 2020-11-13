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
#include <stdio.h>
#include <stdlib.h>

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
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim4);
    int16_t i;

    //int8_t i,j;
    //uint8_t k;
    //i=250;j=7;k=i-j;

    uint8_t *p;
    uint8_t cliBufferTX[200];
    uint8_t cliBufferRX[1024];


    strcpy((char*)cliBufferTX, "Testing CLI!\r\n");
    HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	   i=0;
	   while(i<=10)
	      {
	   	   if((HAL_UART_Receive(&huart2,cliBufferRX, 1,300) == HAL_OK))
	    	 	  {
	   		     cliBufferTX[i] = cliBufferRX[0];
	   		     if( cliBufferTX[i]=='\r')
	   		         break;
	   		     else if( cliBufferTX[i]=='\177')
	   		    	 {
	   		    		p=&cliBufferTX[i];
	   		    		HAL_UART_Transmit(&huart2,p,1,1000);
	   		    		i--;
	   		    		if(i<0)i=0;
	   	             }

	   	        else
	   	        {
	   	        	p=&cliBufferTX[i];
	   	        	HAL_UART_Transmit(&huart2,p,1,1000);
	   	        	i++;
	   	        }
	    	 	 }
	       }

	      cliBufferTX[i]='\0';
	   	  cliBufferRX[0]='\r';
	   	  cliBufferRX[1]='\n';

	   	  HAL_UART_Transmit(&huart2,cliBufferRX,2,1000);

	   	  if(strcmp(cliBufferTX,"turn")==0)
	   	    	  {  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);}

	   	  else if (strcmp(cliBufferTX,"query")==0)
	   	      			  {
	   	      		  	  	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 1)
	   	      		  	  	  {
	   	      		  	  		strcpy((char *)cliBufferTX, "LED on\r\n");
	   	      		  	  		HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *) cliBufferTX), 1000) ;
	   	      		  	  	  }
	   	      		  	  	  else
	   	      		  	  	  {
	   	      		  	  		strcpy((char *)cliBufferTX, "LED off\r\n");
	   	      		  	  		HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char *) cliBufferTX), 1000) ;
	   	      		  	  	  }
	   	      			  }

	   	   else if (strcmp(cliBufferTX,"help")==0)
	   	      	  	  	  {
	   	      		  	  	  strcpy(( char*)cliBufferTX, " enter 'turn' to open and close LED\r\n enter 'query' to see the state of LED\r\n enter 'measure' to measure a number of basic arithmetic operations\r\n enter 'help' to get help\r\n");
	   	      		  	  	  HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   	      	  	  	  }

	   	   else if (strcmp(cliBufferTX,"measure")==0)
	   	      {
	   		        int32_t a_32,b_32;
	   		        int64_t a_64,b_64;
	   		        int16_t previous;
	   		        uint32_t tick1 = 0,tick2 = 0,tick3 = 0,tick4 = 0,tick5 = 0,tick6 = 0;
	   		        for (i = 0; i < 100; i++)
	   		          {
	   		            a_32 = rand();                                                               //generate the random values
	   		            b_32 = rand();
	   		            a_64 = rand();
	   		            b_64 = rand();

	   		            previous = timer_start();
	   		            a_32+b_32;
	   		            tick1 = tick1 + timer_stop(previous);

	   		            previous = timer_start();
	   		            a_64+b_64;
	   		            tick2 = tick2 + timer_stop(previous);

	   		            previous = timer_start();
	   		            a_32*b_32;
	   		            tick3 = tick3 + timer_stop(previous);

	   		            previous = timer_start();
	   		            a_64*b_64;
	   		            tick4 = tick4 + timer_stop(previous);

	   		            previous = timer_start();
	   		            while(!b_32)b_32 = rand();													 //make sure  don't divide by zero.
	   		            a_32/b_32;
	   		            tick5 = tick5 + timer_stop(previous);

	   		            previous = timer_start();
	   		            while(!b_64)b_64 = rand();
	   		            a_64/b_64;
	   		            tick6 = tick6 + timer_stop(previous);


	   		          }

	   		        tick1 = tick1/100;
	   		        tick2 = tick2/100;
	   		        tick3 = tick3/100;
	   		        tick4 = tick4/100;
	   		        tick5 = tick5/100;
	   		        tick6 = tick6/100;

	   		        strcpy((char*)cliBufferTX, "add two random 32-bit integers: ");                    //prints the results on the screen.
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick1);                                                                    //Converts tick to ASCII

	   		        strcpy((char*)cliBufferTX, "add two random 64-bit integers: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick2);

	   		        strcpy((char*)cliBufferTX, "multiply two random 32-bit integers: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick3);

	   		        strcpy((char*)cliBufferTX, "multiply two random 64-bit integers: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick4);

	   		        strcpy((char*)cliBufferTX, "divide two random 32-bit integers: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick5);

	   		        strcpy((char*)cliBufferTX, "divide two random 64-bit integers: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick6);

	   		        tick1 = 0;
	   		        previous = timer_start();
	   		        for (i = 0; i < 8; i++)
	   		           {
	   		        	cliBufferRX[i] = i;
	   		           }
	   		        tick1 = tick1 + timer_stop(previous);

	   		        tick2 = 0;
	   		        previous = timer_start();
	   		        for (i = 0; i < 128; i++)
	   		           {
	   		        	cliBufferRX[i] = i;
	   		           }
	   		        tick2 = tick2 + timer_stop(previous);


	   		        tick3 = 0;
	   		        previous = timer_start();
	   		        for (i = 0; i <1024; i++)
	   		           {
	   		        	cliBufferRX[i] = i;
	   		           }
	   		        tick3 = tick3 + timer_stop(previous);

	   		        strcpy((char*)cliBufferTX, "copy an 8-byte struct using the assignment operator: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick1);

	   		        strcpy((char*)cliBufferTX, "copy an 128-byte struct using the assignment operator: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick2);

	   		        strcpy((char*)cliBufferTX, "copy an 1024-byte struct using the assignment operator: ");
	   		        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   		        tickasc(tick3);
	   	      }
	   	         else
	   	      	  	  	  { strcpy(( char*)cliBufferTX, "error\r\n");
	   	      	  	        HAL_UART_Transmit(&huart2, cliBufferTX, strlen((char*)cliBufferTX),1000);
	   	      	  	  	  }

	   }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

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
  huart2.Init.BaudRate = 9600;
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
