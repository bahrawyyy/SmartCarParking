/*
 * PIR.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */

#ifndef HAL_INCLUDES_PIR_H_
#define HAL_INCLUDES_PIR_H_

#include "Stm32_F103C6_gpio_driver.h"


#define PIR_1		GPIO_PIN_7
#define PIR_2		GPIO_PIN_1

#define PIR_PORT	GPIOA


void PIR_Init(void);
void PIR_Read(uint16_t PIR, uint8_t *pir_reading);

#endif /* HAL_INCLUDES_PIR_H_ */
