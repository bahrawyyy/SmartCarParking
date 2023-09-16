/*
 * Stm32_F103C6_TIMER_driver.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */


#include "Stm32_F103C6_TIMER_driver.h"



void TIMER2_Init(void)
{
	// Enable clock for timer2
	RCC_TIMER2_CLK_EN();

	// Choose a prescalar (8MHz/(7+1)=1MHz clock)
	TIMER2->PSC = 7;


	// Choose a value for auto reload register (we didn't use the maximum value because we doesn't have long delays)
	// Timer 2 will generate an interrupt every 50 milliseconds
	// The auto-reload register (ARR) is used for the purpose of resetting the timer counter back to 0 when it reaches the value specified in ARR.
	// This process is often referred to as "wrapping" or "overflowing."
	TIMER2->ARR = 0xC350;  // 50000*1us = 0.05s

	// Enable Timer2
	TIMER2->CR1 |= (1<<0);


	//Wait until the update flag (UIF) in the status register (SR) of TIM2 becomes 1.
	// This indicates that the timer
	// has finished counting to its ARR value and generated an interrupt.
	while(!((TIMER2->SR) & (1<<0)));
}




void Delay_us(int us)
{
	TIMER2->CNT = 0;
	while((TIMER2->CNT) < us);
}



void Delay_ms(int ms)
{
	int i;
	for(i=0;i<ms;i++)
	{
		Delay_us(1000);
	}
}



