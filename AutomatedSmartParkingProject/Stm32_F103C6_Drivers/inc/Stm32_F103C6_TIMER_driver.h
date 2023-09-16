/*
 * Stm32_F103C6_TIMER_driver.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_TIMER_DRIVER_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_TIMER_DRIVER_H_

#include "stm32f103c6.h"

void TIMER2_Init(void);

void Delay_us(int us);

void Delay_ms(int ms);


#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_TIMER_DRIVER_H_ */
