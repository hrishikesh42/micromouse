/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"
#include "LED_Display.h"
#include "motors.h"
#include "spi.h"
#include "tim.h"
#include "encoder.h"
#include "pdT.h"
#include "pdV.h"
#include "hugger.h"
#include "lock.h"
#include "flood.h"

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
uint32_t leftTicks = 0;
uint32_t rightTicks = 0;

float left_velocity = 0;
float right_velocity = 0;
float angle = 0;

int left_counts = 0;
int left_last_counts = 0;
int right_counts = 0;
int right_last_counts = 0;
float inst_yaw = 0;

int algorithm;
struct dist_maze distances;
struct wall_maze cell_walls_info;
struct stack update_stack;
struct stack move_queue;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM10_Init();
  MX_DMA_Init();

  /* USER CODE BEGIN 2 */
  emitter_Init();
  algorithm = mouseStartSensorWave();
  custom_delay(1000);
  setPositionL(0);
  setPositionR(0);
  setIntegralL(0);
  setIntegralR(0);
  leftMotorStart();
  rightMotorStart();

  MX_TIM11_Init();
  MX_SPI2_Init();
  Init_IMU();
  encoderStart();
  resetLeftEncoder();
  resetRightEncoder();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if (algorithm == 2)
    {
      // Floodfill
      algorithm = wallFavor();
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
      HAL_Delay(1000);

      struct coor target;
      init_coor(&target, 8, 7);
      init_distance_maze(&distances, &target, 1);
      init_wall_maze(&cell_walls_info);
      cell_walls_info.cells[0][0].walls[EAST] = 1;
      cell_walls_info.cells[0][0].walls[SOUTH] = 1;
      cell_walls_info.cells[0][0].walls[WEST] = 1;

      struct coor c;
      init_coor(&c, 0, 0);
      MX_TIM3_Init();
      int direction = NORTH;
      update_stack.index = 0;
      direction = floodFill(&distances, &c, &cell_walls_info, algorithm, direction, &update_stack);
      direction = centerMovement(&cell_walls_info, &c, direction);

      init_coor(&target, 0, 0);
      init_distance_maze(&distances, &target, 0);
      logicalFlood(&distances, &c, &cell_walls_info, direction, direction, &update_stack);
      direction = floodFill(&distances, &c, &cell_walls_info, direction, direction, &update_stack);
//      direction = adjustDirection(direction);
      init_distance_maze(&distances, &c, 1);
      logicalFlood(&distances, &c, &cell_walls_info, direction, direction, &update_stack);
      lockInterruptDisable_TIM3();
//      motorMovement(direction);
      wallFavor();
      custom_delay(1000);
      shortestPath(&distances, &c, &cell_walls_info, direction, direction, &update_stack);
      motorStop();
      turnOnLEDS();
      HAL_Delay(3000);
    }
    else if (algorithm == 1)
    {
      // Right wall hugger
      MX_TIM3_Init();
      while (1)
      {
        setBaseSpeed(40);
        rightWallHugger();
      }
    }
    else if (algorithm == 0)
    {
      // Left wall hugger
      MX_TIM3_Init();
      while (1)
      {
        setBaseSpeed(40);
        leftWallHugger();
      }
    }
    /* USER CODE END WHILE */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB busses clocks
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

  /** Configure the Systick interrupt time
  */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
