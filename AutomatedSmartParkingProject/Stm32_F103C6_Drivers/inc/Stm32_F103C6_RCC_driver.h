/*
 * Stm32_F103C6_RCC_driver.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

// Includes
#include "stm32f103c6.h"


// This driver is mainly implemented to get PCLCK1,PCLCK2
// for the calculations of baud rate in UART driver
// These calculations are based on the assumption that our clock
// comes from HSI only



#define HSI_RC_CLK				(uint32_t)8000000
#define HSE_RC_CLK				(uint32_t)16000000

uint32_t MCAL_RCC_GetSYSCLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
