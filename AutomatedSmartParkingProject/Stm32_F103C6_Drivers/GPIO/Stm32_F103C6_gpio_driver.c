/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdallah
 */


#include "Stm32_F103C6_gpio_driver.h"



uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}





/**================================================================
 * @Fn					- MCAL_GPIO_Init
 * @brief 				- Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @param [in] 			- PinConfig: A pointer to a GPIO_PinConfig_t structure which contains the config info for the specified GPIO peripheral
 * @retval 				- None
 * Note					- Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 						  But LQFP48 has only GPIO A,B, part of C,D exported as external pins from the MCU
 */


void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	// Port configuration register low (GPIOx_CRL) configures PIN 0 >> 7
	// Port configuration register high (GPIOx_CRH) configures PIN 8 >> 15

	volatile uint32_t* config_register = NULL;
	uint8_t PINConfig = 0;
	config_register = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH;
	// Clear CNF[1:0] and MODE[1:0]
	(*config_register) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	// If pin is output
	if(PinConfig->GPIO_MODE == GPIO_MODE_AF_OUTPUT_OPENDRAIN || PinConfig->GPIO_MODE == GPIO_MODE_AF_OUTPUT_PUSHPULL || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OPENDRAIN || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PUSHPULL)
	{
		// Set CNF[1:0] and MODE[1:0]

		// From our header file comparing with TRM, << 2 because CNF has the upper 2 bits
		// & 0x0f because we need the first 4 bits only
		PINConfig = ((((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_OUTPUT_SPEED)) & 0x0f);

	}
	// If pin is input (MODE = 00)
	else
	{
		if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLOATING || PinConfig->GPIO_MODE == GPIO_MODE_Analog)
		{
			// Set CNF[1:0] and MODE = 00, also we don't need to subtract anything
			PINConfig = ((((PinConfig->GPIO_MODE) << 2) | 0x00) & 0x0f);
		}else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT)
		{
			// It doesn't exist within the table of these configurations
			// We read from specs that it should be handled as input floating
			PINConfig = (((GPIO_MODE_INPUT_FLOATING << 2) | 0x00) & 0x0f);
		}else
		{
			// Dealing with Pull up and pull down
			PINConfig = (((GPIO_MODE_INPUT_PULLUP << 2) | 0x00) & 0x0f);
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PULLUP)
			{
				// (Pull up) Table 20. Port bit configuration table, PxODR = 1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;  // It is already shifted by its number (from our configuration)
			}else
			{
				// (Pull down) Table 20. Port bit configuration table, PxODR = 0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);  // It is already shifted by its number (from our configuration)
			}
		}
	}

	// Finally, we just need to shift this variable with the position of the pin, and determine whether it is CRL or CRH
	(*config_register) |= (PINConfig << Get_CRLH_Position(PinConfig->GPIO_PinNumber));


}


/**================================================================
 * @Fn					- MCAL_GPIO_DeInit
 * @brief 				- Reset all the GPIO registers
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @retval 				- None
 * Note					- None
 */



void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	// Manual Reseting rather than using Reset Controller
	//	GPIOx->CRL = 0x44444444;
	//	GPIOx->CRH = 0x44444444;
	//	GPIOx->ODR = 0x00000000;
	////	GPIOx->IDR = ; (Read only, you can't write anything on it);
	//	GPIOx->BRR = 0x00000000;
	//	GPIOx->BSRR = 0x00000000;
	//	GPIOx->LCKR = 0x00000000;



	// Here, we can use the Reset Controller
	// Set and cleared by software as said in TRM
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}else if(GPIOx == GPIOC){
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}else if(GPIOx == GPIOD){
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}else if(GPIOx == GPIOE){
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}
}


/**================================================================
 * @Fn					- MCAL_GPIO_ReadPin
 * @brief 				- Read specific pin
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @param [in] 			- PinNumber: Set Pin Number according to @ref GPIO_PIN_define
 * @retval 				- The input pin value (two values based on @ref GPIO_PIN_STATE)
 * Note					- None
 */


uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	uint8_t bitStatus;
	if(((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_LOW)
	{
		bitStatus = GPIO_PIN_HIGH;
	}else
	{
		bitStatus = GPIO_PIN_LOW;
	}
	return bitStatus;
}



/**================================================================
 * @Fn					- MCAL_GPIO_ReadPort
 * @brief 				- Read the input port value
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @retval 				- The input port value
 * Note					- None
 */


uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t portValue;
	portValue = (uint16_t)(GPIOx->IDR);
	return portValue;
}


/**================================================================
 * @Fn					- MCAL_GPIO_WritePin
 * @brief 				- Write on specific pin
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @param [in] 			- PinNumber: Set Pin Number according to @ref GPIO_PIN_define
 * @param [in] 			- Value: Pin Value
 * @retval 				- None
 * Note					- None
 */


void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if(Value != (uint32_t)GPIO_PIN_LOW)
	{
		// Using ODR (Output data register)
		// GPIOx->ODR |= PinNumber;
		// Using BSRR (Port bit set/reset register) {doesnt't need |= sth)
//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
//		These bits are write-only and can be accessed in Word mode only.
//		0: No action on the corresponding ODRx bit
//		1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}else
	{
//		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
//		These bits are write-only and can be accessed in Word mode only.
//		0: No action on the corresponding ODRx bit
//		1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}



/**================================================================
 * @Fn					- MCAL_GPIO_WritePort
 * @brief 				- Write on the output port
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @param [in] 			- Value: Port Value
 * @retval 				- None
 * Note					- None
 */


void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/**================================================================
 * @Fn					- MCAL_GPIO_TogglePin
 * @brief 				- Toggle specific pin
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @param [in] 			- PinNumber: Set Pin Number according to @ref GPIO_PIN_define
 * @retval 				- None
 * Note					- None
 */


void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}


/**================================================================
 * @Fn					- MCAL_GPIO_LockPin
 * @brief 				- The locking mechanism allows the IO config to be frozen
 * @param [in] 			- GPIOx: where x can be (A..E) depending on the device used (to select which GPIO peripheral)
 * @param [in] 			- PinNumber: Set Pin Number according to @ref GPIO_PIN_define
 * @retval 				- OK if pin config is locked or ERROR if pin is not locked ( @ref GPIO_LOCK)
 * Note					- None
 */


uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
//	Bit 16 LCKK[16]: Lock key
//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	LOCK key writing sequence:
//	Write 1
//	Write 0
//	Write 1
//	Read 0
//	Read 1 (this read is optional but confirms that the lock is active)
//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	Any error in the lock sequence will abort the lock.
//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	These bits are read write but can only be written when the LCKK bit is 0.
//	0: Port configuration not locked
//	1: Port configuration locked

	// Set LCKK[16]
	volatile uint32_t temp = 1<<16;
	// Set LCKy
	temp |= PinNumber;
	//	LOCK key writing sequence:
	//	Write 1
	GPIOx->LCKR = temp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = temp;
	//	Read 0
	temp = GPIOx->LCKR;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16))
	{
		return GPIO_LOCK_OK;
	}else{
		return GPIO_LOCK_ERROR;
	}

}

