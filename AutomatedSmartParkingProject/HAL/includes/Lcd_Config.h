/*
 * Lcd_Config.h
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

//This is a file to define index of pins

// LCD is attached to PORTB

// DIO_U8_PIN_0

#define LCD_MODE FOUR_BIT_MODE

#define EIGHT_BIT_MODE 0
#define FOUR_BIT_MODE 1

// LCD instance 1

#define LCD_1_DATA_PORT 	GPIOB

#define D7_1 GPIO_PIN_15
#define D6_1 GPIO_PIN_14
#define D5_1 GPIO_PIN_13
#define D4_1 GPIO_PIN_12

#define LCD_1_CMD_PORT 		GPIOB

#define RS_1 GPIO_PIN_11
#define EN_1 GPIO_PIN_10


// LCD instance 2

#define LCD_2_DATA_PORT 	GPIOA

#define D7_2 GPIO_PIN_15
#define D6_2 GPIO_PIN_14
#define D5_2 GPIO_PIN_13
#define D4_2 GPIO_PIN_12

#define LCD_2_CMD_PORT 		GPIOA

#define RS_2 GPIO_PIN_5
#define EN_2 GPIO_PIN_6
//#define RW_1 GPIO_PIN_2   // Always GND, not needed


#endif /* HAL_LCD_LCD_CONFIG_H_ */
