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

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int8_t i;flag;
 uint8_t *p;
 uint16_t period;
 uint8_t cliBufferTX[200];
 uint8_t cliBufferRX[20];
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
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_TIM_Base_Start(&htim4);              //running tim4

   strcpy((char*)cliBufferTX, "\x1b[2J");                                         /*clear the screen*/
   HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

   strcpy((char*)cliBufferTX, "\x1b[10;r");                                       /*scroll window*/
   HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

   strcpy((char*)cliBufferTX, "\x1b[10;0H");                                      /*position the cursor*/
   HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

    strcpy((char*)cliBufferTX, "Testing CLI!\r\n");
    HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

    HAL_UART_Receive_IT(&huart3,cliBufferRX, 1);
    i=0;
    period=10000;
    flag=0;
    uint16_t counter=0,temp,timer;
    int8_t  j;
    char data[10],escape[10];
  while (1)
  {
	  timer = __HAL_TIM_GET_COUNTER(&htim4);
	  	  if(flag==3)                        //flag = 3 means change happen
	  	  	    {
	  	  		  if (!(timer%period))
	  	  	  	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

	  	  	    }



	  	  if(timer==0)        //refresh the page every second
	  	   {
	  		  counter++;
	  		  temp = counter;
	  		  for( j=0;j<5;j++) 	//	get formal output
	  		   {  data[4-j]=(temp%10)^0x30;
	  		      temp=temp/10;
	  		   }

	  		  data[5]='\0';
	  		  strcpy((char*)escape, "\x1b[s");                                            /*save cursor*/
	  	      HAL_UART_Transmit(&huart3, escape, strlen((char*)escape),1000);
	  	      strcpy((char*)escape, "\x1b[0;0H");                                         /*cursor go begin*/
	     	      HAL_UART_Transmit(&huart3, escape, strlen((char*)escape),1000);
	     	      HAL_UART_Transmit(&huart3, data, strlen((char*)data),1000);
	     	      strcpy((char*)escape, "\x1b[u");
	     	      HAL_UART_Transmit(&huart3, escape, strlen((char*)escape),1000);

	  	   }

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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  htim4.Init.Prescaler = 99;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart)
{
	//UNUSED(huart);
	cliBufferTX[i] = cliBufferRX[0];
	if( cliBufferTX[i]=='\r')                             //get enter command
	{
		cliBufferTX[i]='\0';                              //end input
		cliBufferRX[0]='\r';                              //putty enter
		cliBufferRX[1]='\n';                              //putty go next line
		HAL_UART_Transmit(&huart3,cliBufferRX,2,1000);
		strcpy((char*)cliBufferRX, "\x1b[s");                                            /*save cursor*/
        HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
        strcpy((char*)cliBufferRX, "\x1b[9;0H");                                         /*cursor at 9.0*/
        HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
        strcpy((char*)cliBufferRX, "\x1b[1J");                                           /*clean the line*/
        HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
        strcpy((char*)cliBufferRX, "\x1b[2;0H");                                         /*光cursor at second line*/
        HAL_UART_Transmit(&huart3, cliBufferRX, strlen((char*)cliBufferRX),1000);
		if(strcmp(cliBufferTX,"turn")==0)
		  {  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
             flag=1;

             strcpy((char*)cliBufferTX, "turn to open and close LED");
             HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);

		  }

		else if (strcmp(cliBufferTX,"query")==0)
		  {
			flag=2;

			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 1)
			  {

				strcpy((char *)cliBufferTX, "LED on");
				HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char *) cliBufferTX),1000) ;

			  }
			else
			  {
				strcpy((char *)cliBufferTX, "LED off");
				HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char *) cliBufferTX),1000) ;

			  }
		   }
		else if (strcmp(cliBufferTX,"change")==0)
		   {  flag=3;
			  if(period==10000)
		      {period=1000;
				strcpy((char *)cliBufferTX, "period:0.1s");
				HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char *) cliBufferTX),1000) ;
		      }

		      else
		      {period=10000;
				strcpy((char *)cliBufferTX, "period:1s");
				HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char *) cliBufferTX),1000) ;
		      }

		   }
		 else if (strcmp(cliBufferTX,"help")==0)
		  	  {
		    	  strcpy(( char*)cliBufferTX, " enter 'turn' to open and close LED\r\n enter 'query' to see the state of LED\r\n enter 'Change'to Change the period of the Blinking light\r\n enter 'help' to get help\r\n");
			  	  HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);
			  }
			 else
			  { strcpy(( char*)cliBufferTX, "error\r\n");
				HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);
			  }
        strcpy((char*)cliBufferTX, "\x1b[u");                                                 /*恢复光标*/
        HAL_UART_Transmit(&huart3, cliBufferTX, strlen((char*)cliBufferTX),1000);
		i=0;
		HAL_UART_Receive_IT(&huart3,cliBufferRX, 1);

	 }

	else if( cliBufferTX[i]=='\177')								//if it is backspace,
		{
		  p=&cliBufferTX[i];
		  HAL_UART_Transmit(&huart3,p,1,1000);
		  i--;
		  if(i<0) i=0;                                              //if it is begin location
		  HAL_UART_Receive_IT(&huart3,cliBufferRX, 1);
		}

	     else                                                       // for normal and correct input
		{
		 p=&cliBufferTX[i];
		 HAL_UART_Transmit(&huart3,p,1,1000);
		 i++;
		 HAL_UART_Receive_IT(&huart3,cliBufferRX, 1);

		}
}
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
