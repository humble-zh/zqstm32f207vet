/******************************************************************************
  FileName: systimer.c
  Author: Li_Zhihong
  Date: 20170209
******************************************************************************/
#include "systimer.h"
#include "stm32f2xx_rcc.h"

#define SYSTEMTICK_PERIOD_MS  1
/* this variable is used to create a time reference incremented by 10ms */
vu32 LocalTime = 0;

void systimer_init(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	
	/* SystTick configuration: an interrupt every 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 1000);

	/* Update the SysTick IRQ priority should be higher than the Ethernet IRQ */
	/* The Localtime should be updated during the Ethernet packets processing */
	NVIC_SetPriority (SysTick_IRQn, 0); 
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	/* Update the LocalTime by adding SYSTEMTICK_PERIOD_MS each SysTick interrupt */
	LocalTime += SYSTEMTICK_PERIOD_MS;
}
