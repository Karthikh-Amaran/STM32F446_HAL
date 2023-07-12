/*
 * it.c
 *
 *  Created on: May 11, 2023
 *      Author: Karthikh Amaran
 */

#include "stm32f4xx_hal.h"
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
