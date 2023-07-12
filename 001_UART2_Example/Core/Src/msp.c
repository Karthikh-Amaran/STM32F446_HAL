/*
 * msp.c
 *
 *  Created on: May 11, 2023
 *      Author: Karthikh Amaran
 */

#include "stm32f4xx_hal.h"
void HAL_MspInit(void)
{
  // Here we weill do low level processor specific inits.
	//1. Setup the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);// This is already NVIC_PRIORITYGROUP_4 by default
	//2. Enable the required system exceptions of the arm cortex mx processor
	/*
	 *  Enabling the Usage Fault, Bus Fault and Memory Fault Exceptions in the System Control Block
	 */
	SCB->SHCSR |= (0x7<<16);
	//3. Configure the priority for the System Exceptions
	// Priority for these exceptions are already at high priority state so better to leave it as default unless you wanted to extensively change it.
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0,0);

}
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	// Here we are going to do low level initialization of the UART Peripheral
	// 1. Enable the Clock for the USART2 and GPIOA Peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// 2. Do the Pin Muxing Configuration
	// PA2 Alternate Function as USART2 TX
	GPIO_InitTypeDef gpio_uart;
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	// PA3 Alternate Function as USART2 RX
	gpio_uart.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	// 3. Enable the IRQ And Setup the priority (NVIC Setting)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}
