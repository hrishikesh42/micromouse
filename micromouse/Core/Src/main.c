/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "SysInit.h"
#include "PWM.h"
#include "ADC.h"
#include "UART.h"
#include "GPIO.h"

int adc_value = 0;

int main(void)
{

	//SYSINIT
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	//PWM
	PWM_Init();            // Initialize PWM
	PWM_SetDutyCycle(50);  // Set duty cycle to 50%
	PWM_Start();           // Start PWM

	//ADC
	ADC_Init();           // Initialize the ADC

	//UART
	UART_Init(9600);         // Initialize UART with baud rate 9600
	UART_SendString("Hello, UART!\n"); // Send a string via UART

	//GPIO
    GPIO_Init_Output(GPIOA, 5);  // Initialize PA5 as output (for LED)
    GPIO_Init_Input(GPIOA, 0);   // Initialize PA0 as input (for button)

    //I2C
    I2C_Init();             // Initialize I2C
    uint8_t data = I2C_Read(0xA0);  // Read a byte from slave device with address 0xA0
    I2C_Write(0xA0, 0x55);          // Write 0x55 to slave device with address 0xA0

	while (1)
	{
		adc_value = ADC_Read();  // Read the ADC value from PA0

		uint8_t received = UART_Receive();   // Receive a byte from UART
		UART_Transmit(&received, 1);         // Echo the received byte back
	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
