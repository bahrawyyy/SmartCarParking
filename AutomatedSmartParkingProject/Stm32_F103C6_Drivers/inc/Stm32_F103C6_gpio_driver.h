/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdallah
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103c6.h"

// ----------------------------------------------- //

// Config Structure, it carry the info related to pins that will be passed to
// init function
// info such input or output, open-drain or push-pull

typedef struct
{
	// This parameter must be set based on @ref GPIO_PIN_define
	uint16_t GPIO_PinNumber;   // Specifies the GPIO pin to be configured

	// This parameter must be set based on @ref GPIO_MODE_define
	uint8_t GPIO_MODE;  // Specifies the operation mode of the selected pin

	// This parameter must be set based on @ref GPIO_SPEED_define
	uint8_t GPIO_OUTPUT_SPEED; // Specifies the speed for the selected pin

}GPIO_PinConfig_t;

// ------------------------------------------------------------------------

//-----------------------------
//Macros Configuration References
//-----------------------------


/* @ref GPIO_PIN_STATE */
#define GPIO_PIN_HIGH     				1
#define GPIO_PIN_LOW					0


/* @ref GPIO_LOCK */
#define GPIO_LOCK_OK     				1
#define GPIO_LOCK_ERROR					0

/* @ref GPIO_PIN_define */

#define GPIO_PIN_0								((uint16_t)0x0001)
#define GPIO_PIN_1								((uint16_t)0x0002)
#define GPIO_PIN_2								((uint16_t)0x0004) // 1<<2
#define GPIO_PIN_3								((uint16_t)0x0008)
#define GPIO_PIN_4								((uint16_t)0x0010)
#define GPIO_PIN_5								((uint16_t)0x0020)
#define GPIO_PIN_6								((uint16_t)0x0040)
#define GPIO_PIN_7								((uint16_t)0x0080)
#define GPIO_PIN_8								((uint16_t)0x0100)
#define GPIO_PIN_9								((uint16_t)0x0200)
#define GPIO_PIN_10								((uint16_t)0x0400)
#define GPIO_PIN_11								((uint16_t)0x0800)
#define GPIO_PIN_12								((uint16_t)0x1000)
#define GPIO_PIN_13								((uint16_t)0x2000)
#define GPIO_PIN_14								((uint16_t)0x4000)
#define GPIO_PIN_15								((uint16_t)0x8000) // 1<<15
#define GPIO_PIN_ALL							((uint16_t)0xFFFF)

#define GPIO_PIN_MASK							0x0000FFFFu  /* PIN Mask to select the first four bytes



//@ref GPIO_MODE_define */

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input

#define GPIO_MODE_Analog									0x00000000u  // Analog mode
#define GPIO_MODE_INPUT_FLOATING							0x00000001u  // Floating input
#define GPIO_MODE_INPUT_PULLUP								0x00000002u  // Input with pull-up
#define GPIO_MODE_INPUT_PULLDOWN							0x00000003u  // Input with pull-down
#define GPIO_MODE_OUTPUT_PUSHPULL							0x00000004u  // General purpose output push-pull
#define GPIO_MODE_OUTPUT_OPENDRAIN							0x00000005u  // General purpose output Open-drain
#define GPIO_MODE_AF_OUTPUT_PUSHPULL						0x00000006u  // Alternate function output Push-pull
#define GPIO_MODE_AF_OUTPUT_OPENDRAIN						0x00000007u  // Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT									0x00000008u  // Alternate function input


/* @ref GPIO_SPEED_define */
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.

#define GPIO_SPEED_10MHZ									0x00000001u  // Output mode, max speed 10 MHz
#define GPIO_SPEED_2MHZ										0x00000002u  // Output mode, max speed 2 MHz
#define GPIO_SPEED_50MHZ									0x00000003u  // Output mode, max speed 50 MHz


// -----------------------------------------------------------------------------------------------------


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/


void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);  /* The user should send the base address of the wanted GPIO, and the configuration of this pin */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);


#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
